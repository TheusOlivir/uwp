//
// MainPage.xaml.h
// Declaração da classe MainPage.
//

#pragma once

#include "MainPage.g.h"

namespace Monetario
{
	/// <summary>
	/// Uma página vazia que pode ser usada isoladamente ou navegada dentro de um Quadro.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		void OnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void MainPage::StartButtonAnimation();
		void MainPage::StopButtonAnimation();
		void MainPage::OnTimerTick(Platform::Object^ sender, Platform::Object^ e);

        Windows::UI::Xaml::DispatcherTimer^ m_dispatcherTimer;
        int m_animationStep;
	};
}
