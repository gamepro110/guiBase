#pragma once

#include <imgui.h>
#include "misc/cpp/imgui_stdlib.h"

namespace guiBase {
    class Layer {
    public:
        virtual ~Layer() = default;

    public:
        virtual void onAttach() {
        }
        virtual void onUpdate() {
        }
        virtual void onDetach() {
        }

    protected:
        /// <summary>
        /// copy of `HelpMarker` found in `vendor/imgui/imgui_demo.cpp`
        /// </summary>
        /// <param name="info">text to be displayed in the tooltip</param>
        static void InfoMarker(const char* info) {
            ImGui::TextDisabled("(?)");
            if (ImGui::BeginItemTooltip()) {
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted(info);
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
        }
    };
}// namespace guiBase
