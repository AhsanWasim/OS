#include<iostream>
#include<cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


struct Point;
const int gridlines();
bool check_collision(float, float, float, float);
Point check_food_collision1(float, float, Sprite**, int);

struct Point{

int x;
int y;

};


const int gridlines(){

	srand(unsigned(time(0)));

	const int max = 99, min = 10, roll = 0440;

	int num = rand()%(max - min +1) + min;
	
	num *= 0; 		// last num of roll num is 0 

	int result = num / roll;
	result %= 25;


	if(result < 10){

	result += 15;
	}

	return result;
}

bool check_collision(float cor1x, float cor2x, float cor1y, float cor2y){

int size = 20;
int sizey = 40;

if((int)cor1x + size < (int)cor2x)
{
	return false;
}
if((int)cor2x + size < (int)cor1x){
	return false;
}
if((int)cor1y + sizey < (int)cor2y){
	return false;
}
if((int)cor2y + sizey < (int)cor1y){
	return false;
}

return true;
} 


Point check_food_collision(float x, float y, Sprite** arr, int size){

	int sizex = 20;
	int sizey = 40;
	Point point;

	for(int i = 0; i < size ; i++){
		for(int j =0 ; j < size ; j++){
			if ((int)x + sizex >= (int)arr[i][j].getPosition().x && (int)arr[i][j].getPosition().x + sizex >= (int)x && (int)y + sizey >= (int)arr[i][j].getPosition().y && (int)arr[i][j].getPosition().y + sizey >= (int)y) {
        
			point.x = i;
			point.y = j;
			return point;
			}
		}
	}	
point.x = -1;
point.y = -1;
return point;
}





int main()
{   

	const int result = gridlines();

	const int size_of_block = 40;
	const int horizontal_end = 20;
	const int verticle_end = 50;

	RenderWindow window(VideoMode(750, 600), "ThreadGame");



//	LINES



	VertexArray line(Lines, 2*(result+result));

	for(int i =0; i< result; i++){

	line[i * 2].position = Vector2f(0.f, i * size_of_block);
    line[i * 2].color = Color::Black;
	line[(i*2)+1].position = sf::Vector2f(horizontal_end*size_of_block, i * size_of_block);
    line[(i*2)+1].color = sf::Color::Black;

	}

	for(int i =0; i< result; i++){

	line[2 * (i + result)].position = Vector2f(i * verticle_end, 0.f);
    line[2 * (i + result)].color = Color::Black;
	line[2 * (i + result)+1].position = sf::Vector2f(i * verticle_end, result * size_of_block);
    line[2 * (i + result)+1].color = sf::Color::Black;

	}


	
//	SPRITE

	Texture texture;
	if(!texture.loadFromFile("charachter.png")){

		cout<<"\nSprite ERROR!!!\n";

	}
	
	Texture texture2;
	if(!texture2.loadFromFile("charachter2.png")){

		cout<<"\nSprite2 ERROR!!!\n";

	}
	
	Sprite charachter(texture);
	charachter.setScale(Vector2f(60.f / texture.getSize().x, 60.f / texture.getSize().y));


	Sprite charachter2(texture2);
	charachter2.setScale(Vector2f(60.f / texture2.getSize().x, 60.f / texture2.getSize().y));
	charachter2.setPosition(550.f, 550.f);

	
int size = result -5;

	Sprite** food_arr = new Sprite* [size];

	for(int i = 0 ; i < size ; i++){
		food_arr[i] = new Sprite[size];
	}

	float xfood = 60.f;
	float yfood = 40.f; 

	Texture texture3;
	if(!texture3.loadFromFile("cake.png")){

		cout<<"\nFood ERROR!!!\n";
	}
	
	for(int i = 0; i < size ; i++){
		for(int j =0 ; j < size ; j++){

		food_arr[i][j].setTexture(texture3);
		food_arr[i][j].setScale(Vector2f(40.f / texture3.getSize().x, 40.f / texture3.getSize().y));
		food_arr[i][j].setPosition(xfood, yfood);
		xfood += 60;
		}
		xfood = 60.f;
		yfood += 50;
	}

	float Speedx = 100.f;
	float Speedy = 100.f;

	Clock clock;
	Point point;

	while (window.isOpen())
	{

		Time deltatime = clock.restart();
		float dt = deltatime.asSeconds();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


// Player 1

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{

		if(check_food_collision(charachter.getPosition().x, charachter.getPosition().y, food_arr, size).x != -1){

			point = check_food_collision(charachter.getPosition().x, charachter.getPosition().y, food_arr, size);
			food_arr[point.x][point.y].setPosition(999.f, 999.f);
		}

		if(charachter.getPosition().x < 0) continue;

		if(!check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
    	charachter.move( -Speedx * dt, 0.f);
		}
		else {
			charachter.move(-40 * dt, 0.f);
		}
		}


        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
		
		if(check_food_collision(charachter.getPosition().x, charachter.getPosition().y, food_arr, size).x != -1){

			point = check_food_collision(charachter.getPosition().x, charachter.getPosition().y, food_arr, size);
			food_arr[point.x][point.y].setPosition(999.f, 999.f);
		}
		if(charachter.getPosition().x > 700) continue;

		if(!check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y))
		{	
       	charachter.move( Speedx * dt, 0.f);
		}
		else {
			charachter.move(40 * dt, 0.f);
		}
        }


		if (Keyboard::isKeyPressed(Keyboard::Up))
        {
			if(check_food_collision(charachter.getPosition().x, charachter.getPosition().y, food_arr, size).x != -1){

			point = check_food_collision(charachter.getPosition().x, charachter.getPosition().y, food_arr, size);
			food_arr[point.x][point.y].setPosition(999.f, 999.f);
		}

		if(charachter.getPosition().y < 0) continue;

		if(!check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
       	charachter.move(0.f, -Speedy * dt);
        }
		else {
			charachter.move(0.f, -40 * dt);
		}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
        {
		if(check_food_collision(charachter.getPosition().x, charachter.getPosition().y, food_arr, size).x != -1){

			point = check_food_collision(charachter.getPosition().x, charachter.getPosition().y, food_arr, size);
			food_arr[point.x][point.y].setPosition(999.f, 999.f);
		}

		if(charachter.getPosition().y > 550) continue;

		if(!check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
       	charachter.move(0.f, Speedy * dt);
		}
		else {
			charachter.move(0.f, 40 * dt);
		}
		}

// Player 2

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
		if (check_food_collision(charachter2.getPosition().x, charachter2.getPosition().y, food_arr, size).x != -1) {

    	point = check_food_collision(charachter2.getPosition().x, charachter2.getPosition().y, food_arr, size);
    	food_arr[point.x][point.y].setPosition(999.f, 999.f);

		}

		if(charachter2.getPosition().x < 0) continue;

		if(!check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
		charachter2.move( -Speedx * dt, 0.f);
		}
		else {
			charachter2.move(-40 * dt, 0.f);
		}
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{

		if (check_food_collision(charachter2.getPosition().x, charachter2.getPosition().y, food_arr, size).x != -1) {

    	point = check_food_collision(charachter2.getPosition().x, charachter2.getPosition().y, food_arr, size);
    	food_arr[point.x][point.y].setPosition(999.f, 999.f);
		
		}

		if(charachter2.getPosition().x > 700) continue;

		if(!check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
		charachter2.move( Speedx * dt, 0.f);
		}
		else {
			charachter2.move(40 * dt, 0.f);
		}
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{

		if (check_food_collision(charachter2.getPosition().x, charachter2.getPosition().y, food_arr, size).x != -1) {

    	point = check_food_collision(charachter2.getPosition().x, charachter2.getPosition().y, food_arr, size);
    	food_arr[point.x][point.y].setPosition(999.f, 999.f);
		
		}

		if(charachter2.getPosition().y < 0) continue;

		if(!check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
		charachter2.move(0.f, -Speedy * dt);
		}
		else {
			charachter2.move(0.f, -40 * dt);
		}
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
		if (check_food_collision(charachter2.getPosition().x, charachter2.getPosition().y, food_arr, size).x != -1) {

    	point = check_food_collision(charachter2.getPosition().x, charachter2.getPosition().y, food_arr, size);
    	food_arr[point.x][point.y].setPosition(999.f, 999.f);
		
		}

		if(charachter2.getPosition().y > 550) continue;

		if(!check_collision(charachter.getPosition().x, charachter2.getPosition().x, charachter.getPosition().y, charachter2.getPosition().y)){
		charachter2.move(0.f, Speedy * dt);
		}
		else {
			charachter2.move(0.f, 40 * dt);
		}
		}

		window.clear(Color::Cyan);
		window.draw(line);
		window.draw(charachter);
		window.draw(charachter2);

		for(int i = 0 ; i < size ; i++){
			for(int j = 0 ; j< size ; j++){
			window.draw(food_arr[i][j]);
			}
		}
		window.display();
	}
}
