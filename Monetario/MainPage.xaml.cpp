#include "pch.h"
#include "MainPage.xaml.h"

using namespace Monetario;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
	InitializeComponent();
}

void MainPage::OnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Inicie a animação do botão
	StartButtonAnimation();

	// Obtenha o CPF do textBox e concatene-o ao link base
	Platform::String^ cpf = textBox->Text;
	Platform::String^ url = "https://buscatextual.cnpq.br/buscatextual/busca.do?metodo=forwardPaginaResultados&registros=0%3B10&query=idx_cpf%3A" + cpf;

	// Faça a requisição HTTP e coloque o HTML retornado no textBlock2
	auto httpClient = ref new Windows::Web::Http::HttpClient();
	concurrency::create_task(httpClient->GetStringAsync(ref new Windows::Foundation::Uri(url))).then([this](Platform::String^ result)
	{
		// Atualize o textBlock2 com o resultado e pare a animação do botão
		textBlock2->Text = result;
		StopButtonAnimation();
	});
}

void MainPage::StartButtonAnimation()
{
	// Crie um DispatcherTimer para atualizar o texto do botão
	m_dispatcherTimer = ref new Windows::UI::Xaml::DispatcherTimer();
	TimeSpan ts;
	ts.Duration = 500 * 10000; // 500ms
	m_dispatcherTimer->Interval = ts;
	m_dispatcherTimer->Tick += ref new EventHandler<Object^>(this, &MainPage::OnTimerTick);
	m_animationStep = 0;
	m_dispatcherTimer->Start();
}

void MainPage::StopButtonAnimation()
{
	if (m_dispatcherTimer != nullptr)
	{
		m_dispatcherTimer->Stop();
		m_dispatcherTimer = nullptr;
	}
	// Restaure o texto original do botão
	button->Content = L"Let's Go";
}

void MainPage::OnTimerTick(Platform::Object^ sender, Platform::Object^ e)
{
	m_animationStep = (m_animationStep + 1) % 4;
	Platform::String^ buttonText = L"Buscando";
	for (int i = 0; i < m_animationStep; ++i)
	{
		buttonText += ".";
	}
	button->Content = buttonText;
}
