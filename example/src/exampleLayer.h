#pragma once

#include "guiBase/App.h"
#include "guiBase/Layer.h"
#include "guiBase/Logger.h"
#include "guiBase/bit_stuff.h"

#include "imgui.h"

class exampleLayer final : public guiBase::Layer {
public:
    exampleLayer() = default;

public:
    void onAttach() override {
        bitValue--;
    }

    void onUpdate() override {
        if (ImGui::Begin("example", nullptr, windowFlags)) {
            ImGui::PushButtonRepeat(true);
            if (ImGui::Button("+")) {
                bitValue++;
                LOG_TRACE("bitValue++");
            }
            ImGui::SameLine();
            if (ImGui::Button("-")) {
                bitValue--;
                LOG_TRACE("bitValue--");
            }
            ImGui::PopButtonRepeat();

            ImGui::SameLine();
            guiBase::intToBin(printStr, bitValue);
            ImGui::Text("uint8_t: %03d  0x%02x", bitValue, bitValue);
            ImGui::SameLine();
            ImGui::Text("%s", printStr.c_str());
            ImGui::Separator();
        }
        ImGui::End();
    }

    void onDetach() override {
    }

private:
    uint8_t bitValue{ 0 };
    std::string printStr{};
    ImGuiWindowFlags windowFlags{ 0 | ImGuiWindowFlags_AlwaysAutoResize };
};
