#include "utility.h"

#include <cmath>
#include <stack>

Direction Utility::mouseDirectionFromObject(float delta_x, float delta_y) {
    if (delta_x < -abs(delta_y)) {
        return Direction::Left;
    } else if (delta_x > abs(delta_y)) {
        return Direction::Right;
    } else if (delta_y > abs(delta_x)) {
        return Direction::Up;
    }
    return Direction::Down; // delta_y < -abs(delta_x)
}

std::vector<sf::Vector2i> Utility::getNeighbours(sf::Vector2i pair, int map_size) {
    std::vector<sf::Vector2i> neighbours;
    int i = pair.x;
    int j = pair.y;
    if (i > 0) {
        neighbours.push_back({i - 1, j});
    }
    if (j > 0) {
        neighbours.push_back({i, j - 1});
    }
    if (i < map_size - 1) {
        neighbours.push_back({i + 1, j});
    }
    if(j < map_size - 1){
        neighbours.push_back({i, j + 1});
    }
    if(j > 0 && i > 0){
        neighbours.push_back({i - 1, j - 1});
    }
    if(j > 0 && i < map_size - 1){
        neighbours.push_back({i + 1, j - 1});
    }
    if (j < map_size - 1 && i < map_size - 1) {
        neighbours.push_back({i + 1, j + 1});
    }
    if(i > 0 && j < map_size - 1){
        neighbours.push_back({i - 1, j + 1});
    }

    return neighbours;
}

void  Utility::pathFinder(const std::vector<std::vector<bool>> &map, std::queue<sf::Vector2f> &trajectory,sf::Vector2f start, sf::Vector2f end) {
    sf::Vector2i m_start = {int(start.y), int(start.x)};
    sf::Vector2i m_end = {int(end.y), int(end.x)};
    std::vector<std::vector<int>> steps(map.size(), std::vector<int>(map.size(), -1));
    steps[m_start.x][m_start.y] = 0;

    std::queue<sf::Vector2i> Q;
    Q.push(m_start);

    bool hasEnd = false;
    while(!(Q.empty()))
    {
        sf::Vector2i next = Q.front();
        Q.pop();


        if(next.x == m_end.x && next.y == m_end.y){
            hasEnd = true;
            break;
        }
        std::vector<sf::Vector2i> neighbours = getNeighbours(next, map.size());
        for(int  k = 0; k < neighbours.size(); ++k)
        {
            size_t i = neighbours[k].x;
            size_t j = neighbours[k].y;
            if(map[i][j] == 0 && steps[i][j] == -1){
                Q.push(neighbours[k]);
                steps[i][j] = steps[next.x][next.y] + 1;
            }
        }
    }

    std::stack<sf::Vector2i> path;
    path.push(m_end);
    if(hasEnd){

        while(path.top().x != m_start.x || path.top().y != m_start.y)
        {
            sf::Vector2i current = path.top();
            std::vector<sf::Vector2i> neighbours = getNeighbours(current, map.size());
            for(int  k = 0; k < neighbours.size(); ++k){
                size_t i = neighbours[k].x;
                size_t j = neighbours[k].y;
                if(steps[i][j] == steps[current.x][current.y] - 1){
                    path.push(neighbours[k]);
                    break;
                }
            }
        }
    }else{
        path.pop();
        Q.push(m_end);

        while(!(Q.empty()))
        {
            sf::Vector2i next = Q.front();
            Q.pop();


            if(steps[next.x][next.y] > -1){
                path.push(next);
                break;
            }
            std::vector<sf::Vector2i> neighbours = getNeighbours(next, map.size());
            for(int  k = 0; k < neighbours.size(); ++k)
            {
                size_t i = neighbours[k].x;
                size_t j = neighbours[k].y;
                if(steps[i][j] >= -1){
                    Q.push(neighbours[k]);
                    if(steps[i][j] == -1){
                        steps[i][j]--;
                    }
                }
            }
            
        }

        while(!path.empty() && (path.top().x != m_start.x || path.top().y != m_start.y))
        {
            sf::Vector2i current = path.top();
            std::vector<sf::Vector2i> neighbours = getNeighbours(current, map.size());
            for(int  k = 0; k < neighbours.size(); ++k){
                size_t i = neighbours[k].x;
                size_t j = neighbours[k].y;
                if(steps[i][j] == steps[current.x][current.y] - 1){
                    path.push(neighbours[k]);
                    break;
                }
            }
        }

    }

    trajectory.push(start);
    path.pop();
    
    while(path.size() > 1)
    {
        trajectory.push({static_cast<float>(path.top().y), static_cast<float>(path.top().x)});
        path.pop();
    }
    if(hasEnd){
        trajectory.push(end);
    }else{
        trajectory.push({static_cast<float>(path.top().y), static_cast<float>(path.top().x)});
        path.pop();
    }
}
