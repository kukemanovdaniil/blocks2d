#include "uiManager.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

UiManager::UiManager() noexcept = default;

UiManager::~UiManager() {
    if (m_isInitialized) {
        ImGui::SFML::Shutdown();
    }
}

std::expected<void, std::string> UiManager::init(sf::RenderWindow& window) {
    if (!ImGui::SFML::Init(window)) {
        return std::unexpected("error init uiManager");
    }

    m_isInitialized = true;
    
    applyCustomTheme();

    return {};
}

void UiManager::handleEvent(const sf::RenderWindow& window, const sf::Event& event) noexcept {
    if (m_isInitialized) {
        ImGui::SFML::ProcessEvent(window, event);
    }
}

void UiManager::beginFrame(sf::RenderWindow& window) noexcept {
    if (m_isInitialized) {
        ImGui::SFML::Update(window, m_deltaClock.restart());
    }
}

void UiManager::endFrame(sf::RenderWindow& window) noexcept {
    if (m_isInitialized) {
        ImGui::SFML::Render(window);
    }
}

void UiManager::applyCustomTheme() noexcept {
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Скругления для кнопок и окон
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    
    // Цветовая палитра
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.90f); 
    colors[ImGuiCol_Button]   = ImVec4(0.25f, 0.40f, 0.65f, 1.00f); 
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.50f, 0.78f, 1.00f);
}