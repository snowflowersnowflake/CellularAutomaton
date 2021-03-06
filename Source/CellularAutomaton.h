#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Util/Config.h"

class Application;

class CellularAutomaton
{
    public:
        CellularAutomaton(const Config& config, const Application& app);
        virtual ~CellularAutomaton() = default;

        virtual void input(const sf::Event& e) {}
        virtual void update() = 0;
        virtual void onRenderGUI(sf::RenderWindow& window) {};
        virtual void onRenderCells(sf::RenderWindow& window) {};
        void render(sf::RenderWindow& window);

        void makeScreenshot();
    
    protected:
        unsigned getCellIndex(unsigned x, unsigned y);

        void setCellColour(int x, int y, sf::Color colour);

        template<typename Func>
        void cellForEach(Func function);

        const Application* const m_pApplication;
        const Config* const m_pConfig;
        void addQuad(unsigned xIndex, unsigned yIndex);
        std::vector<sf::Vertex> m_cellVertexPoints;
};

template<typename Func>
void CellularAutomaton::cellForEach(Func function)
{
    for (unsigned y = 0; y < m_pConfig->simSize.y; y++) {
        for (unsigned x = 0; x < m_pConfig->simSize.x; x++) {
            function(x, y);
        }
    }
}