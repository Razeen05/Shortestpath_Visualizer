#include "SFML/Graphics.hpp"//graphics library
#include "Box.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm> 
#include <ctime>

using namespace std; 
int pathf=1;//variable to check path is found or not
void BFS(vector<vector<Box*>>& b, sf::RenderWindow& window, int startX, int startY);//function declaration

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Path Finding");

    int count = 0;//Initialize
    int startX = 0;
    int startY = 0;

    int endX;
    int endY;

    vector<vector<Box*>> boxes;
    for (int i = 0; i < 72; i++) {
        vector<Box*> temp;
        boxes.push_back(temp);
    }
	//72 rows and 128 columns
    for (int i = 0; i < 72; i++) {
        for (int j = 0; j < 128; j++) {
            Box* b = new Box(j * 10, i * 10);
            boxes[i].push_back(b);
        }
    }

   clock_t startTime, endTime;

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePosition;//for mouseposition

        while (window.pollEvent(event)) {//always check for the events
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//left mouse click to mark obstacles
                mousePosition = sf::Mouse::getPosition(window);

                int x = 0, y = 0; // Initialize 
                x = mousePosition.x / 10;
                y = mousePosition.y / 10;
                boxes[y][x]->body.setFillColor(sf::Color::Black);//black
                boxes[y][x]->type = 1;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {//space button to start 
                if (count == 0) {
                	cout<<"----------------------------------BFS visualizer----------------------------------------------"<<endl;
                       
                    
                    // Start measuring time
                    startTime = clock();

                    BFS(boxes, window, startX, startY);//bfs function call

                    // End measuring time
                    if(pathf){
                    endTime = clock();
                    float totalTime = ((float)(endTime - startTime)) / CLOCKS_PER_SEC;
                    cout << "Total time to find the path: " << totalTime << " seconds" << endl;//time
                    }

                    count++;
                }
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//s to mark start position
                mousePosition = sf::Mouse::getPosition(window);
                int x = 0, y = 0; // Initialize 
                startX = mousePosition.x / 10;
                startY = mousePosition.y / 10;
                boxes[startY][startX]->body.setFillColor(sf::Color::Green);//green
                boxes[startY][startX]->type = 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {//e to mark end position
                mousePosition = sf::Mouse::getPosition(window);
                int x = 0, y = 0; // Initialize 
                endX = mousePosition.x / 10;
                endY = mousePosition.y / 10;
                boxes[endY][endX]->body.setFillColor(sf::Color::Red);//red
                boxes[endY][endX]->type = 3;
            }
        }

        // draws state to screen
        window.clear(sf::Color::White);
        for (int i = 0; i < 72; i++) {
            for (int j = 0; j < 128; j++) {
                window.draw(boxes[i][j]->body);
            }
        }
        window.display();
    }
}

void BFS(vector<vector<Box*>>& b, sf::RenderWindow& window, int startX, int startY) {
    vector<Box*> visited;//vector for visibility of boxes
    vector<Box*> queue;//queue to implement bfs

    int yPos = startY;//start position
    int xPos = startX;
    visited.push_back(b[yPos][xPos]);
    visited[0]->xLocation = xPos;
    visited[0]->yLocation = yPos;
    visited[0]->visited = true;
    int g1=1;
    while (visited[visited.size() - 1]->type != 3) {
        xPos = visited[visited.size() - 1]->xLocation;
        yPos = visited[visited.size() - 1]->yLocation;
         g1++;
        // add adjacent vertices to queue
        // north
        if (yPos - 1 >= 0 && b[yPos - 1][xPos]->visited == false && (b[yPos - 1][xPos]->type == 0 || b[yPos - 1][xPos]->type == 3)) {
            queue.push_back(b[yPos - 1][xPos]);
            b[yPos - 1][xPos]->xLocation = xPos;
            b[yPos - 1][xPos]->yLocation = yPos - 1;
            b[yPos - 1][xPos]->prev = b[yPos][xPos];
            queue[queue.size() - 1]->body.setFillColor(sf::Color::Magenta);
            queue[queue.size() - 1]->visited = true;
        }
        // south
        if (yPos + 1 <= 71 && b[yPos + 1][xPos]->visited == false && (b[yPos + 1][xPos]->type == 0 || b[yPos + 1][xPos]->type == 3)) {
            queue.push_back(b[yPos + 1][xPos]);
            b[yPos + 1][xPos]->xLocation = xPos;
            b[yPos + 1][xPos]->yLocation = yPos + 1;
            b[yPos + 1][xPos]->prev = b[yPos][xPos];
            queue[queue.size() - 1]->body.setFillColor(sf::Color::Magenta);
            queue[queue.size() - 1]->visited = true;
        }
        // west
        if (xPos - 1 >= 0 && b[yPos][xPos - 1]->visited == false && (b[yPos][xPos - 1]->type == 0 || b[yPos][xPos - 1]->type == 3)) {
            queue.push_back(b[yPos][xPos - 1]);
            b[yPos][xPos - 1]->xLocation = xPos - 1;
            b[yPos][xPos - 1]->yLocation = yPos;
            b[yPos][xPos - 1]->prev = b[yPos][xPos];
            queue[queue.size()- 1]->body.setFillColor(sf::Color::Magenta);
            queue[queue.size() - 1]->visited = true;
        }
        // east
        if (xPos + 1 <= 127 && b[yPos][xPos + 1]->visited == false && (b[yPos][xPos + 1]->type == 0 || b[yPos][xPos + 1]->type == 3)) {
            queue.push_back(b[yPos][xPos + 1]);
            b[yPos][xPos + 1]->xLocation = xPos + 1;
            b[yPos][xPos + 1]->yLocation = yPos;
            b[yPos][xPos + 1]->prev = b[yPos][xPos];
            queue[queue.size() - 1]->body.setFillColor(sf::Color::Magenta);
            queue[queue.size() - 1]->visited = true;
        }

        // check queue is not empty
        // add first item in queue to visited
        if (!queue.empty()) {
            visited.push_back(queue[0]);
            // remove first item in queue
            queue.erase(queue.begin());
        }
        else{
        	cout<<"path is not found"<<endl;
        	pathf=0;
        	break;
        	
        	}

        visited[visited.size() - 1]->body.setFillColor(sf::Color::Blue);

        // redraw display
        window.clear(sf::Color::White);
        for (int i = 0; i < 72; i++) {
            for (int j = 0; j < 128; j++) {
                window.draw(b[i][j]->body);
            }
        }
        window.display();
    }
    if(pathf){

    Box* temp = visited[visited.size() - 1];
    int countr=0;
    vector<pair<int,int>>lp;
    while (temp->prev != nullptr) {//backtrack to find path 
        countr++;
        lp.push_back({temp->xLocation,temp->yLocation});
        temp->body.setFillColor(sf::Color::Yellow);
        temp = temp->prev;
    }
    lp.push_back({temp->xLocation,temp->yLocation});
    reverse(lp.begin(),lp.end());
    cout<<"path is: ";
    for(int i=0;i<lp.size();i++){//path printing
        cout<<"("<<lp[i].second<<","<<lp[i].first<<")"<<"->";
    }
    cout<<endl;
    cout<<"path length from start point to end is:"<<countr+1<<endl; 
    cout<<"total boxes accessed to find the path is:"<<g1<<endl;
    }

}


