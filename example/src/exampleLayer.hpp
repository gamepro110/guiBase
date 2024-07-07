#pragma once

#include "guiBase/App.hpp"
#include "guiBase/Layer.hpp"
#include "guiBase/Logger.hpp"
#include "guiBase/bit_stuff.hpp"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

class exampleLayer final : public guiBase::Layer {
public:
    exampleLayer() = default;

public:
    void onAttach() override {
        bitValue--;
        memset(buff, '\0', IM_ARRAYSIZE(buff));
    }

    void onUpdate() override {
        if (ImGui::Begin("example", nullptr, windowFlags)) {
            ImGui::InputText("label", buff, IM_ARRAYSIZE(buff));

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

            ImGui::InputTextMultiline("input with <std::string>", &text);
        }
        ImGui::End();
    }

    void onDetach() override {
    }

private:
    char buff[100];
    uint8_t bitValue{ 0 };
    std::string printStr{};
    ImGuiWindowFlags windowFlags{ 0 | ImGuiWindowFlags_AlwaysAutoResize };
    [[maybe_unused]] std::string text;
};
