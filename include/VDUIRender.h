#pragma once

#include "cinder/app/App.h"

// UserInterface
#include "CinderImGui.h"
// Settings
#include "VDSettings.h"
// Session
#include "VDSession.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace videodromm
{
	// stores the pointer to the VDUIRender instance
	typedef std::shared_ptr<class VDUIRender> VDUIRenderRef;

	class VDUIRender
	{
	public:
		VDUIRender(VDSettingsRef aVDSettings, VDSessionRef aVDSession);
		static VDUIRenderRef	create(VDSettingsRef aVDSettings, VDSessionRef aVDSession)
		{
			return shared_ptr<VDUIRender>(new VDUIRender(aVDSettings, aVDSession));
		}
		void    Run(const char* title);
	private:
		// Settings
		VDSettingsRef					mVDSettings;
		// Session
		VDSessionRef					mVDSession;
		float							getValue(unsigned int aCtrl);
		float							getValueByName(string aCtrlName);
		void							setValue(unsigned int aCtrl, float aValue);
		void							toggleAuto(unsigned int aCtrl);
		void							toggleTempo(unsigned int aCtrl);
		void							toggleSpoutSender();
		bool							getBoolValue(unsigned int aCtrl);
		void							toggleValue(unsigned int aCtrl);
		void							resetAutoAnimation(unsigned int aCtrl);
		float							getMinUniformValueByIndex(unsigned int aIndex);
		float							getMaxUniformValueByIndex(unsigned int aIndex);
		void							setIntValue(unsigned int aCtrl, int aValue);
		int								getIntValue(unsigned int aCtrl);
		// imgui
		int								ctrl;
		float							contour, iVAmount, iVFallOff;
		int								iResolutionX, iResolutionY;
		int								iOutW, iOutH;
		// contour
		float							minContour;
		float							maxContour;
		// imgui
		char						buf[64];
		int							xPos, yPos;
	};
}