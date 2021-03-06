#include "VDUIFbos.h"

using namespace videodromm;

VDUIFbos::VDUIFbos(VDSettingsRef aVDSettings, VDSessionRef aVDSession) {
	mVDSettings = aVDSettings;
	mVDSession = aVDSession;
}

void VDUIFbos::Run(const char* title) {

	/*
	** textures
	*/
	static int XLeft[64];
	static int YTop[64];
	static int XRight[64];
	static int YBottom[64];
	static bool rnd[64];
	static bool anim[64];
	/*
	for (int t = 0; t < mVDSession->getInputTexturesCount(); t++) {
		xPos = mVDSettings->uiMargin + mVDSettings->uiXPosCol1 + ((mVDSettings->uiLargePreviewW + mVDSettings->uiMargin) * t);
		yPos = mVDSettings->uiYPosRow2;

		ImGui::SetNextWindowSize(ImVec2(mVDSettings->uiLargePreviewW, mVDSettings->uiLargePreviewH), ImGuiSetCond_Once);
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiSetCond_Once);
		int hue = 0;
		sprintf(buf, "%s##s%d", mVDSession->getInputTextureName(t).c_str(), t);
		ImGui::Begin(buf, NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
		{
			ImGui::PushItemWidth(mVDSettings->mPreviewFboWidth);
			ImGui::PushID(t);
			ImGui::Image((void*)mVDSession->getInputTexture(t)->getId(), ivec2(mVDSettings->mPreviewFboWidth, mVDSettings->mPreviewFboHeight));
			ImGui::PushItemWidth(mVDSettings->mPreviewFboWidth * 0.7);
			// flip vertically
			mVDSession->isFlipVInputTexture(t) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			sprintf(buf, "FlipV##vd%d", t);
			if (ImGui::Button(buf)) {
				mVDSession->inputTextureFlipV(t);
			}
			ImGui::PopStyleColor(3);
			hue++;
			ImGui::SameLine();
			// flip horizontally
			mVDSession->isFlipHInputTexture(t) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			sprintf(buf, "FlipH##hd%d", t);
			if (ImGui::Button(buf)) {
				mVDSession->inputTextureFlipH(t);
			}
			ImGui::PopStyleColor(3);
			hue++;

			//for (unsigned int f = 0; f < mVDMix->getWarpCount(); f++) {
			//if (f > 0) ImGui::SameLine();
			////int ti = mVDMix->getFboInputTextureIndex(f);
			////CI_LOG_V("fbo" + toString(f) + " t" + toString(t) + " ti" + toString(ti));
			//if (mVDMix->getWarpATextureIndex(f) == t) {
			//ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 1.0f, 1.0f));
			//}
			//else {
			//ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 0.1f, 0.1f));
			//}
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(t / 7.0f, 0.7f, 0.7f));
			//ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(t / 7.0f, 0.8f, 0.8f));
			//sprintf(buf, "%d##fboinputtex%d%d", f, t, f);
			//if (ImGui::Button(buf)) mVDMix->setFboInputTexture(f, t);
			//if (ImGui::IsItemHovered()) ImGui::SetTooltip("Set input texture for warp");
			//ImGui::PopStyleColor(3);
			//}

			//sprintf(buf, "WS##s%d", i);
			//if (ImGui::Button(buf))
			//{
			//sprintf(buf, "IMG=%d.jpg", i);
			////mVDRouter->wsWrite(buf);
			//}
			//if (ImGui::IsItemHovered()) ImGui::SetTooltip("Send texture file name via WebSockets");
			//

			if (mVDSession->isSequence(t) || mVDSession->isMovie(t)) {
				sprintf(buf, "p##s%d", t);
				if (ImGui::Button(buf))
				{
					mVDSession->togglePlayPause(t);
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Play/Pause");
			}
			if (mVDSession->isSequence(t)) {
				ImGui::SameLine();
				sprintf(buf, "b##sqs%d", t);
				if (ImGui::Button(buf))
				{
					mVDSession->syncToBeat(t);
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Sync to beat");

				ImGui::SameLine();
				sprintf(buf, "r##rs%d", t);
				if (ImGui::Button(buf))
				{
					mVDSession->reverse(t);
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Reverse");

				if (mVDSession->isLoadingFromDisk(t)) {
					ImGui::SameLine();
					sprintf(buf, "l##ts%d", t);
					if (ImGui::Button(buf))
					{
						mVDSession->toggleLoadingFromDisk(t);
					}
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Pause loading from disk");
				}
				speeds[t] = mVDSession->getSpeed(t);
				sprintf(buf, "speed##spd%d", t);
				if (ImGui::SliderFloat(buf, &speeds[t], 0.0f, 1.0f))
				{
					mVDSession->setSpeed(t, speeds[t]);
				}

				playheadPositions[t] = mVDSession->getPosition(t);
				sprintf(buf, "scrub##srb%d", t);
				if (ImGui::SliderInt(buf, &playheadPositions[t], 0, mVDSession->getMaxFrame(t)))
				{
					mVDSession->setPlayheadPosition(t, playheadPositions[t]);
				}


			}
			else {
				if (!mVDSession->isMovie(t)) {
					// not a sequence nor video, animate x y...
					XLeft[t] = mVDSession->getInputTextureXLeft(t);
					if (anim[t]) {
						if (rnd[t]) {
							XLeft[t] += xStep * Rand::randBool();
						}
						else {
							XLeft[t] += xStep;
						}
						// check bounds 
						if (XLeft[t] < 1) {
							xStep = -xStep;
						}
						if (XLeft[t] > mVDSession->getInputTextureOriginalWidth(t) - mVDSettings->mFboWidth - 1) {
							xStep = -xStep;
						}
					}
					sprintf(buf, "XL##xl%d", t);
					ImGui::SliderInt(buf, &XLeft[t], 0, mVDSession->getInputTextureOriginalWidth(t));// CHECK - mVDSettings->mFboWidth
					mVDSession->setInputTextureXLeft(t, XLeft[t]);

					YTop[t] = mVDSession->getInputTextureYTop(t);
					if (anim[t]) {
						if (rnd[t]) {
							YTop[t] += yStep * Rand::randBool();
						}
						else {
							YTop[t] += yStep;
						}
						// check bounds
						if (YTop[t] < 1) {
							yStep = -yStep;
						}
						if (YTop[t] > mVDSession->getInputTextureOriginalHeight(t) - mVDSettings->mFboHeight - 1) {
							yStep = -yStep;
						}
					}
					sprintf(buf, "YT##yt%d", t);
					ImGui::SliderInt(buf, &YTop[t], 0, mVDSession->getInputTextureOriginalHeight(t));// - mVDSettings->mFboHeight
					mVDSession->setInputTextureYTop(t, YTop[t]);


					ImGui::SameLine();
					(mVDSession->getInputTextureLockBounds(t)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
					sprintf(buf, "8##lk%d", t);
					if (ImGui::Button(buf)) {
						mVDSession->toggleInputTextureLockBounds(t);
					}
					ImGui::PopStyleColor(3);
					hue++;

					XRight[t] = mVDSession->getInputTextureXRight(t);
					sprintf(buf, "XR##xr%d", t);
					if (ImGui::SliderInt(buf, &XRight[t], 0, mVDSession->getInputTextureOriginalWidth(t))) {
						mVDSession->setInputTextureXRight(t, XRight[t]);
					}
					ImGui::SameLine();
					(anim[t]) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
					sprintf(buf, "ani##r%d", t);
					anim[t] ^= ImGui::Button(buf);
					ImGui::PopStyleColor(3);
					hue++;

					YBottom[t] = mVDSession->getInputTextureYBottom(t);
					sprintf(buf, "YB##yb%d", t);
					if (ImGui::SliderInt(buf, &YBottom[t], 0, mVDSession->getInputTextureOriginalHeight(t))) {
						mVDSession->setInputTextureYBottom(t, YBottom[t]);
					}

					ImGui::SameLine();
					(rnd[t]) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
					sprintf(buf, "rnd##r%d", t);
					rnd[t] ^= ImGui::Button(buf);
					ImGui::PopStyleColor(3);
					hue++;
				}
			}
			ImGui::PopItemWidth();
			ImGui::PopID();
			ImGui::PopItemWidth();
		}
		ImGui::End();
	}
	*/

#pragma region mix
int w = 0;
xPos = mVDSettings->uiMargin + mVDSettings->uiXPosCol1;
yPos = mVDSettings->uiYPosRow2;// - mVDSettings->uiLargePreviewH

ImGui::SetNextWindowSize(ImVec2(mVDSettings->uiLargePreviewW, mVDSettings->uiLargePreviewH), ImGuiSetCond_Once);
ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiSetCond_Once);
/*
sprintf(buf, "%s##sh%d", "mix", 0);
ImGui::Begin(buf, NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
{
	ImGui::PushItemWidth(mVDSettings->mPreviewFboWidth);
	ImGui::Image((void*)mVDSession->getMixTexture(w)->getId(), ivec2(mVDSettings->mPreviewFboWidth, mVDSettings->mPreviewFboHeight));
	// crossfade
	float xFade = mVDSession->getCrossfade();// getWarpCrossfade(w);
	sprintf(buf, "xfade##xf%d", w);
	if (ImGui::SliderFloat(buf, &xFade, 0.0f, 1.0f))
	{
		mVDSession->setCrossfade(xFade);
	}

	for (int s = 0; s < mVDSession->getShadersCount(); s++) {
		int f = 0;
		if (s > 0 && (s % 9 != 0)) ImGui::SameLine();
			
		if (mVDSession->getFboFragmentShaderIndex(f) == s) {
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 1.0f, 0.5f));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.1f, 0.1f));
		}
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.8f));
		sprintf(buf, "%d##sf%d", s, f);
		if (ImGui::Button(buf)) mVDSession->setFboFragmentShaderIndex(f, s);
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("Set fbo to left");
		ImGui::PopStyleColor(3);
	}
	for (int s = 0; s < mVDSession->getShadersCount(); s++) {
		int f = 1;
		if (s > 0 && (s % 9 != 0)) ImGui::SameLine();

		if (mVDSession->getFboFragmentShaderIndex(f) == s) {
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 1.0f, 0.5f));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.1f, 0.1f));
		}
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.8f));
		sprintf(buf, "%d##sf%d", s, f);
		if (ImGui::Button(buf)) mVDSession->setFboFragmentShaderIndex(f, s);
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("Set shader to right");
		ImGui::PopStyleColor(3);
	}

	ImGui::PopItemWidth();
}
ImGui::End();
*/
#pragma endregion mix
#pragma region fbos

	/*
	** fbos
	*/
	for (unsigned int f = 0; f < mVDSession->getFboListSize(); f++) {//mVDSession->getFboListSize() or 2
		xPos = mVDSettings->uiMargin + mVDSettings->uiXPosCol1 + ((mVDSettings->uiLargePreviewW + mVDSettings->uiMargin) * (f));//+1
		yPos = mVDSettings->uiYPosRow2;
		ImGui::SetNextWindowSize(ImVec2(mVDSettings->uiLargePreviewW, mVDSettings->uiLargePreviewH), ImGuiSetCond_Once);
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiSetCond_Once);
		sprintf(buf, "%s##fbolbl%d", mVDSession->getFboName(f).c_str(), f);
		ImGui::Begin(buf, NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
		{
			ImGui::PushID(f);
			ImGui::Image((void*)mVDSession->getFboRenderedTexture(f)->getId(), ivec2(mVDSettings->mPreviewFboWidth, mVDSettings->mPreviewFboHeight));
			// causes loss of resolution: 
			//if (ImGui::IsItemHovered()) mVDSession->getFboTexture(f);
			for (unsigned int t = 0; t < mVDSession->getInputTexturesCount(); t++) {
				if (t > 0 && (t % 6 != 0)) ImGui::SameLine();
				if (mVDSession->getFboInputTextureIndex(f) == t) {
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 1.0f, 1.0f));
				}
				else {
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 0.1f, 0.1f));
				}
				sprintf(buf, "%d##fboit%d%d", t, f, t);
				if (ImGui::Button(buf)) mVDSession->setFboInputTexture(f, t);

				sprintf(buf, "Set input texture to %s", mVDSession->getInputTextureName(t).c_str());
				if (ImGui::IsItemHovered()) ImGui::SetTooltip(buf);
				ImGui::PopStyleColor(1);
			}
			if (mVDSession->isFboFlipV(f)) {
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(f / 7.0f, 1.0f, 1.0f));
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(f / 7.0f, 0.1f, 0.1f));
			}
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(f / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(f / 7.0f, 0.8f, 0.8f));
			sprintf(buf, "FlipV##fboflipv%d", f);
			if (ImGui::Button(buf)) mVDSession->fboFlipV(f);
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			sprintf(buf, "T##fboupd%d", f);
			if (ImGui::Button(buf)) mVDSession->updateShaderThumbFile(f);
			ImGui::Text("wh %dx%d", mVDSession->getFboRenderedTexture(f)->getWidth(), mVDSession->getFboRenderedTexture(f)->getHeight());
			ImGui::PopID();
		}
		ImGui::End();
	}
	
#pragma endregion fbos

}
