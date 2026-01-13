#pragma once
#include <d3d9.h>
#include <fstream>
#include <string>
#include <windows.h>
#include "../XrEUI/imgui.h"

namespace Colors {
    bool showGui = false;

    // --- Переменные цветов ---
    float windowBg[4] = { 0.1f, 0.1f, 0.1f, 0.95f };
    float accentColor[4] = { 0.2f, 0.5f, 0.9f, 1.0f };
    float text[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    const char* configFileName = "ui_settings.cfg";

    /**
     * Сохранение данных в файл
     */
    inline void SaveSettings() {
        std::ofstream file(configFileName);
        if (file.is_open()) {
            file << windowBg[0] << " " << windowBg[1] << " " << windowBg[2] << " " << windowBg[3] << "\n";
            file << accentColor[0] << " " << accentColor[1] << " " << accentColor[2] << " " << accentColor[3] << "\n";
            file << text[0] << " " << text[1] << " " << text[2] << " " << text[3] << "\n";
            file.close();
        }
    }

    /**
     * Загрузка данных из файла
     */
    inline void LoadSettings() {
        std::ifstream file(configFileName);
        if (file.is_open()) {
            file >> windowBg[0] >> windowBg[1] >> windowBg[2] >> windowBg[3];
            file >> accentColor[0] >> accentColor[1] >> accentColor[2] >> accentColor[3];
            file >> text[0] >> text[1] >> text[2] >> text[3];
            file.close();
        }
    }

    /**
     * Применяет цвета к стилю ImGui
     */
    inline void UpdateImGuiStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4 accent = ImVec4(accentColor[0], accentColor[1], accentColor[2], accentColor[3]);
        ImVec4 accentHovered = ImVec4(accent.x * 1.1f, accent.y * 1.1f, accent.z * 1.1f, accent.w);
        ImVec4 accentActive = ImVec4(accent.x * 0.8f, accent.y * 0.8f, accent.z * 0.8f, accent.w);

        style.Colors[ImGuiCol_WindowBg] = ImVec4(windowBg[0], windowBg[1], windowBg[2], windowBg[3]);
        style.Colors[ImGuiCol_Text] = ImVec4(text[0], text[1], text[2], text[3]);

        // Кнопки и заголовки
        style.Colors[ImGuiCol_Header] = accent;
        style.Colors[ImGuiCol_HeaderHovered] = accentHovered;
        style.Colors[ImGuiCol_HeaderActive] = accentActive;
        style.Colors[ImGuiCol_Button] = accent;
        style.Colors[ImGuiCol_ButtonHovered] = accentHovered;
        style.Colors[ImGuiCol_ButtonActive] = accentActive;
        style.Colors[ImGuiCol_TitleBgActive] = accent;
        // --- Добавлено: заголовки и границы ---
        style.Colors[ImGuiCol_TitleBg] = ImVec4(accent.x * 0.6f, accent.y * 0.6f, accent.z * 0.6f, 0.8f);
        style.Colors[ImGuiCol_Separator] = ImVec4(accent.x, accent.y, accent.z, 0.5f);

        // Поля ввода, чекбоксы и слайдеры
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.5f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.2f, 0.2f, 0.5f);
        style.Colors[ImGuiCol_FrameBgActive] = accentActive;
        style.Colors[ImGuiCol_CheckMark] = accent;
        style.Colors[ImGuiCol_SliderGrab] = accent;
        style.Colors[ImGuiCol_SliderGrabActive] = accentActive;

        // --- дополнительные элементы ---
        style.Colors[ImGuiCol_PlotLines] = accent;              // Графики (линии)
        style.Colors[ImGuiCol_PlotLinesHovered] = accentHovered;
        style.Colors[ImGuiCol_PlotHistogram] = accent;          // Графики (бары/гистограммы)
        style.Colors[ImGuiCol_PlotHistogramHovered] = accentHovered;
        style.Colors[ImGuiCol_ResizeGrip] = accent;             // Уголок изменения размера
        style.Colors[ImGuiCol_ResizeGripHovered] = accentHovered;
        style.Colors[ImGuiCol_ResizeGripActive] = accentActive;
        style.Colors[ImGuiCol_SeparatorHovered] = accentHovered;
        style.Colors[ImGuiCol_SeparatorActive] = accentActive;
        style.Colors[ImGuiCol_Tab] = accent;
        style.Colors[ImGuiCol_TabHovered] = accentHovered;
        style.Colors[ImGuiCol_TabActive] = accentActive;
        style.Colors[ImGuiCol_TabUnfocusedActive] = accent;

        // --- ПОЛНЫЙ ПЕРЕКРАС ВСЕХ СИНИХ ЧАСТЕЙ ---
        style.Colors[ImGuiCol_ScrollbarGrab] = accent;          // Ползунок прокрутки
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = accentHovered;
        style.Colors[ImGuiCol_ScrollbarGrabActive] = accentActive;
        style.Colors[ImGuiCol_SliderGrab] = accent;             // Хваталка слайдера
        style.Colors[ImGuiCol_SliderGrabActive] = accentActive;
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(accent.x, accent.y, accent.z, 0.35f); // Выделение текста
        style.Colors[ImGuiCol_DragDropTarget] = accent;         // Цвет при перетаскивании элементов
        style.Colors[ImGuiCol_NavHighlight] = accent;           // Рамка фокуса навигации (клавиатура/геймпад)
    }

    inline void Enable() {
        showGui = true;
    }

    inline void Disable() {
        showGui = false;
    }

    inline bool IsOpen() { return showGui; }

    inline void Render() {
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            if (showGui) Disable();
            else Enable();
        }

        if (!showGui) return;

        ImGui::SetNextWindowSize(ImVec2(350, 0), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("Style Settings", &showGui, ImGuiWindowFlags_AlwaysAutoResize)) {
            bool changed = false;

            ImGui::TextDisabled("Controls:");
            if (ImGui::Button("Hide Menu (Insert)", ImVec2(-1, 0))) {
                Disable();
            }

            ImGui::Separator();
            ImGui::Text("Color Palette:");

            if (ImGui::ColorEdit4("Background", windowBg))   changed = true;
            if (ImGui::ColorEdit4("Accent Color", accentColor)) changed = true;
            if (ImGui::ColorEdit4("Text Color", text))       changed = true;

            if (changed) UpdateImGuiStyle();

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::Button("Save Config", ImVec2(120, 0))) {
                SaveSettings();
            }

            if (ImGui::Button("Load Config", ImVec2(120, 0))) {
                LoadSettings();
                UpdateImGuiStyle();
            }

            ImGui::SameLine();

            if (ImGui::Button("Reset Defaults", ImVec2(-1, 0))) {
                windowBg[0] = 0.1f; windowBg[1] = 0.1f; windowBg[2] = 0.1f; windowBg[3] = 0.95f;
                accentColor[0] = 0.2f; accentColor[1] = 0.5f; accentColor[2] = 0.9f; accentColor[3] = 1.0f;
                text[0] = 1.0f; text[1] = 1.0f; text[2] = 1.0f; text[3] = 1.0f;
                UpdateImGuiStyle();
            }
        }
        ImGui::End();

        if (!showGui) {
            Disable();
        }
    }
}