/*02.03.2018 - 20.03.2018
 * All the numbers regarding the sprites for the game objects
 * are set for this particular sprites. If you change the sprites, you
 * will have to also change them.*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#define playerScale 0.4
#define espawnLimit 60 // timer for spawning the enemies
#define enemyScale 0.45
#define backgroundScalex 1 //0.5
#define backgroundScaley 1 //0.5
#define width window.getSize().x
#define heigth window.getSize().y

using namespace sf;

int main()
{
	// Initial VARIABLES--------------------------------------------------------------
	
	/* 'go' for the state of game
	 * 0 for game over
	 * 1 for initial text
	 * 2 for casual gameplay 
	 * 3 for instructions
	 * 4 for selecting the difficulty level
	 * 5 for difficult gameplay*/
	int go = 1; 
	int health = 100;
	float playerx = 0, playery = 0; // player's coordinates
	int score = 0;
	srand(time(NULL));
	Vector2f playerCenter;
	Vector2f enemyCenter;
    int shootTimer = 0; // timer for the creation of player's projectiles
    int eshootTimer = 0; // timer for the creation of enemies' projectiles
    int enemySpawnTimer = 0;
    int instrdelay = 0; // delay between enter pressing to show the instructions
	int heartTimer = 700; // spawning time of the hearts
	int shieldTimer = 0; // spawning time of the shields
	bool fieldState = false; // the state of the force field
	int fieldLimit = 0; // for monitoring the time the field is on
	std::string fi = "       GAME OVER!\n";
	std::string sc = "SCORE ";
    std::string scspace = "        SCORE ";
	float hsspeed = 4.f; // speed of the hearts and shields
	int heartSpawn = 2500; // timer for spawning the hearts
	int shieldSpawn = 2500; // timer for spawning the hearts
	int fieldTime = 600; // the time the field is on
	int enemyLife = 3; // it takes 3 shots to kill a difficulty level enemy
	int enemyX = 0;
	float espeed = 1.f;
	int enemyShootLimit = 50; // timer limit for the enemy shooting
	
	// Add MUSIC----------------------------------------------------------------------
	Music music;
	if(!music.openFromFile("soundtrack.ogg"))
		std::cout<<"ERROR"<<std::endl;
		
	music.play();
	
	
	// Create the WINDOW--------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "LASERMACHT", Style::Fullscreen);//
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    
    
    // BACKGROUND image---------------------------------------------------------------
    Texture background;
	if(!background.loadFromFile("background.jpg")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	Texture background2;
	if(!background2.loadFromFile("background2.jpg")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	Texture background3;
	if(!background3.loadFromFile("background3.jpg")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	
	Sprite back;
	back.setTexture(background);
	back.setScale(backgroundScalex, backgroundScaley);
	
    
    // TEXT---------------------------------------------------------------------------
   
    // Choose the font
    Font font;
	if(!font.loadFromFile("data-latin.ttf")){
		std::cout << "Error loading file" << std::endl;
		system("pause");
	}
	
	
	// Score and health text----------------------------------------------------------
	// Also it is turned in the game over text
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition(width-115, heigth/2-110);// right text position
	
    
    // Intro text---------------------------------------------------------------------
    Text intro;
	intro.setFont(font);
	intro.setCharacterSize(40);
    std::string itr = "WELCOME TO LASERMACHT!\n\n\n"
                      "PRESS ENTER TO PLAY...\n"
                      " PRESS ESC TO EXIT...";
    intro.setPosition(width/2-180, heigth/2-120);
    
    
    // Instructions text--------------------------------------------------------------
    Text instr; 
    instr.setFont(font);
	instr.setCharacterSize(30);
    std::string sinstr = " MOVE LEFT AND RIGHT USING THE MOUSE,\n"
						 "         USE SPACE TO SHOOT,\n"
						 "           PRESS Q TO QUIT\n\n"
						 "       PRESS ENTER TO CONTINUE...\n"
						 "          PRESS ESC TO EXIT...";
    instr.setPosition(width/2-230, heigth/2-90);
    instr.setString(sinstr);
    
    
    // Difficulty level-----------------------------------------------------------------
    Text diff;
    diff.setFont(font);
    diff.setCharacterSize(30);
    std::string diffstr = "CHOOSE THE TYPE OF THE GAME\n\n"
						 "    CASUAL    (PRESS 1)\n"
						 "    DIFFICULT (PRESS 2)";
    
    diff.setPosition(width/2-200, heigth/2-90);
    diff.setString(diffstr);
    
    
    
    // Create the PLAYER'S PROJECTILE-------------------------------------------------
    Texture bullet;
	if(!bullet.loadFromFile("bullet.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	Sprite projectile;
	projectile.setTexture(bullet);
	projectile.setScale(1.4, 1.4);
	
	
	
    
    // Create the PLAYER--------------------------------------------------------------
	Texture texture;
	if(!texture.loadFromFile("unnamed.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	Sprite player;
	player.setTexture(texture);
	player.setPosition(width/2-20, heigth-125);
	player.setScale(playerScale, playerScale);
	
	
	
    
    // Create ENEMY'S PROJECTILE------------------------------------------------------
    Texture ebullet;
	if(!ebullet.loadFromFile("ebullet.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	Texture ebullet2;
	if(!ebullet2.loadFromFile("bullet2.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	
	
	Sprite eprojectile;
	eprojectile.setTexture(ebullet);
	eprojectile.setScale(0.07, 0.07);
	
	
	
    
    // Create the ENEMY---------------------------------------------------------------
    // Casual level enemy ship
    Texture etexture;
	if(!etexture.loadFromFile("eship.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	// Difficult level enemy ship-------------------------------------------------------
	Texture etexture2;
	if(!etexture2.loadFromFile("eship2.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	
	Sprite enemy;
	enemy.setTexture(etexture);
	enemy.setScale(enemyScale,enemyScale);
	enemy.setRotation(180);
	
	
	
	
	// Create the HEARTS--------------------------------------------------------------
	Texture heart;
	if(!heart.loadFromFile("heart.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	Sprite life;
	life.setTexture(heart);
	life.setScale(0.06,0.06);
	
	
	
	
	// Create the SHIELDS-------------------------------------------------------------
	Texture shield;
	if(!shield.loadFromFile("shield.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	
	Sprite armor;
	armor.setTexture(shield);
	armor.setScale(0.04,0.04);
	
	


    // Create the FORCE FIELD---------------------------------------------------------
    Texture force;
	if(!force.loadFromFile("forcefield2.png")){
		std::cout<<"Load failed"<<std::endl;
		system("pause");
	}
	Sprite field;
	field.setTexture(force);
	field.setScale(0.6,0.6); // 1.1
	//field.setColor(Color::Cyan);
	
    
    
    // Create VECTORS ----------------------------------------------------------------
    std::vector<Sprite> enemies; // vector for the enemies
    std::vector<Sprite> projectiles; // vector for player's projectiles
    std::vector<Sprite> eprojectiles; // vector for all enemies' projectiles
    std::vector<int> eshootTimers; // vector for shooting timer of each enemy
    std::vector<Sprite> hearts; // vector for all the hearts
    std::vector<Sprite> shields; // vector for all the shields
    std::vector<int> enemyLives; // vector for each enemy life
    std::vector<int> enemyXmove; // vector for the amount of left and right movement of the enemies
    
    
    
	//---------------------------------------------------------------GAME LOOP-----------------------------------------------------------------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Set the timers for hearts, shields and field--------------------------------
        if(go == 2){
			heartSpawn = 2500; 
			shieldSpawn = 2500; 
			fieldTime = 600;
			enemyShootLimit = 50;
			
		}
		
        if(go == 5){
			heartSpawn = 3000; 
			shieldSpawn = 3000; 
			fieldTime = 450;
			heartTimer = 1000;
			enemyShootLimit = 80;
		}
        
        
        
		
		
		// -----------------------------UPDATE----------------------------------------
		
		// HEARTS
		if(heartTimer < heartSpawn){
			heartTimer++;
			}
		
		// create the hearts randomly and push them in the vector
		if(heartTimer >= heartSpawn){
			life.setPosition((rand()%int(width-215)) + 80, 0.f);
			hearts.push_back(Sprite(life));
			heartTimer = 0;
		}
		
		// Move the hearts------------------------------------------------------------
		for(size_t i = 0; i < hearts.size(); i++){
			hearts[i].move(0.f, hsspeed); // move the hearts and set speed
			// Remove the hearts when is outside of the screen
			if(hearts[i].getPosition().y >= heigth)
				hearts.erase(hearts.begin() + i);
		}
		
		
		
		
		// SHIELDS--------------------------------------------------------------------
		if(shieldTimer < shieldSpawn){
			shieldTimer++;
			}
		
		// create the shields randomly and push them in the vector
		if(shieldTimer >= shieldSpawn){
			armor.setPosition((rand()%int(width-215)) + 80, 0.f);
			shields.push_back(Sprite(armor));
			shieldTimer = 0;
		}
		
		// Move the shields-----------------------------------------------------------
		for(size_t i = 0; i < shields.size(); i++){
			shields[i].move(0.f, hsspeed); // move the hearts and set speed
			// Remove the hearts when they get outside of the screen
			if(shields[i].getPosition().y >= heigth)
				shields.erase(shields.begin() + i);
		}
		
		
	
		
		
		// PLAYER---------------------------------------------------------------------
		
		// Move the player
		playerCenter = Vector2f(player.getPosition().x+54, player.getPosition().y-25); 
		
		playerx = Mouse::getPosition(window).x-58;
		playery = player.getPosition().y;
		
		
		
		// limits player's movement to the window limits
		if(playerx >= (width - 215))
			player.setPosition(width - 215, playery);
		else if(playerx <= -10)
			player.setPosition(-10, playery);
		else
			player.setPosition(playerx, playery);
			
		// FORCE FIELD----------------------------------------------------------------
		// limits field's movement to the window limits
		if(playerx >= (width - 215))
			field.setPosition(width - 230, playery-22);
		else if(playerx <= -10)
			field.setPosition(-25, playery-22);
		else
			field.setPosition(playerx-15, playery-22);
			
		
		// PlLAYER'S PROJECTILES------------------------------------------------------
		
		// Projectile's creation timer
		if(shootTimer < 12){
			shootTimer++;
		}
		
		// Create projectiles
		if(Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 12){ // Shoot by pressing space
			projectile.setPosition(playerCenter);
			projectiles.push_back(Sprite(projectile));
			shootTimer = 0; // set the timer back to 0
		}
		
		// Move projectiles and erase them if they will pass beyond limits
		for(size_t i = 0; i < projectiles.size(); i++){
			projectiles[i].move(0.f, -10.f); // move the projectile and set speed
			// Remove the projectiles when is outside of the screen
			if(projectiles[i].getPosition().y <= 0)
				projectiles.erase(projectiles.begin() + i);
		}
		
		
		
		
		
		
		// ENEMIES--------------------------------------------------------------------
		
		// Create enemies only if the game is on
		if((go == 2) || (go == 5)){ 
			if (go == 2)
				enemy.setTexture(etexture);
			else if (go == 5)
				enemy.setTexture(etexture2);
			
			// verify the spawn limit
			if(enemySpawnTimer < espawnLimit)
				enemySpawnTimer++;
			
			if(enemySpawnTimer >= espawnLimit){
				enemy.setPosition((rand()%int(width-215)) + 80, 0.f); // set a new random position
				bool colchk = true;
				// verify for collision between enemies
				for(size_t i = 0; i < enemies.size(); i++){
					if(enemy.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
						colchk = false;
				}
				
				if(colchk){
					enemies.push_back(Sprite(enemy)); // push a new enemy to the vector only if there is no collision 
					eshootTimers.push_back(int(eshootTimer)); // create a shoot timer for each enemy
					
					if(go == 5){
						enemyLives.push_back(int(enemyLife)); // create a life for each enemy 
						enemyXmove.push_back(bool(enemyX));
					}
					
					enemySpawnTimer = 0;
				}
				
			}
		}
		
		
		
		
		// MOVE the ENEMIES-----------------------------------------------------------
		for(size_t i = 0; i < enemies.size(); i++){
			// for the casual game simply move the enemies twoards the player
			if(go == 2) {
				espeed = 4.f;
				enemies[i].move(0.f, espeed);
			}
			
			//for the difficult level also move the emenies left and right
			if(go == 5 ){
				espeed = 1.f; // y speed
				enemies[i].move(0.f, espeed);
				
				// move the enemy 50 times right
				if(enemyXmove[i] <= 50){
					enemies[i].move(3.5f, espeed);
					enemyXmove[i]++;
					}
				
				// move the enemy 50 times left
				if(enemyXmove[i] > 50){
					enemies[i].move(-3.5f, espeed);
					enemyXmove[i]++;
				}
				
				// reset the variable for left/right movement to 0
				if(enemyXmove[i] > 100)
					enemyXmove[i] = 0;
			}
			
			// erase the enemies that go beyond window limit, the vectors asociated to them and reduce score
			if(enemies[i].getPosition().y > heigth){
				enemies.erase(enemies.begin() + i); // erase the enemey when passing beyond the screen
				eshootTimers.erase(eshootTimers.begin() + i); // erase the shooting timer
				if (go == 5) { // also erase its live constant because otherwise bugs appears
					enemyLives.erase(enemyLives.begin() + i); 
					eprojectiles.erase(eprojectiles.begin() + i); // erase the projectiles for each erased enemy 				
					enemyXmove.erase(enemyXmove.begin() + i); // erase the variable for the left/right movement
				}
				score--;
			}
		}
		
		
		// Create the projectiles for each enemy--------------------------------------
		for(size_t i = 0; i < enemies.size(); i++){
			if(eshootTimers[i] <= enemyShootLimit)
				eshootTimers[i]++;
			enemyCenter = Vector2f(enemies[i].getPosition().x-58, enemies[i].getPosition().y-20);
			if(eshootTimers[i] >= enemyShootLimit){
				
				
				// different projectile sprites for each type of game 
				if(go == 2){
					eprojectile.setTexture(ebullet);
					eprojectile.setRotation(0);
					eprojectile.setScale(0.07, 0.07);
					enemyCenter = Vector2f(enemies[i].getPosition().x-58, enemies[i].getPosition().y-20);
				}
				
				
				if(go == 5){
					eprojectile.setTexture(ebullet2);
					eprojectile.setRotation(0);
					eprojectile.setScale(0.07, 0.07);
					enemyCenter = Vector2f(enemies[i].getPosition().x-52, enemies[i].getPosition().y-25);
					
				}
				
				
				eprojectile.setPosition(enemyCenter);
				eprojectiles.push_back(Sprite(eprojectile));
				eshootTimers[i] = 0;
			}
			
		}
		
		
		// Move the enemy projectiles-------------------------------------------------
		for(size_t i = 0; i < eprojectiles.size(); i++){
			eprojectiles[i].move(0.f, 10.f);
			// Remove the projectiles when is outside of the screen
			if(eprojectiles[i].getPosition().y >= heigth)
				eprojectiles.erase(eprojectiles.begin() + i);
		}
		
		
		
		
		
		
		// COLLISION between player's projectiles and enemies-------------------------
		for (size_t i = 0; i < projectiles.size(); i++){
			for (size_t k = 0; k < enemies.size(); k++){
				if (projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()) && go == 2){
					projectiles.erase(projectiles.begin() + i);
					enemies.erase(enemies.begin() + k);
					score++; // increase the score when an enemy is hit
					break;
				}
				
				if (projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()) && go == 5){
					
					projectiles.erase(projectiles.begin() + i);
					
					// erase the enemies and their variables
					if(enemyLives[k] <= 1){
						enemies.erase(enemies.begin() + k);
						enemyLives.erase(enemyLives.begin() + k); 
						eprojectiles.erase(eprojectiles.begin() + k); // erase the projectiles for each erased enemy 
						eshootTimers.erase(eshootTimers.begin() + k); // erase the shooting timer
						enemyXmove.erase(enemyXmove.begin() + k);
						score++; // increase the score when an enemy is hit
						break;
					}
					else{
						enemyLives[k]--;
						break;
					}
				}
				
			}
		}
		
		
		
		
		
		
		// COLLISION between enemies' projectiles and player--------------------------
		for(size_t i = 0; i < eprojectiles.size(); i++){
			// collision only if the field is off
			if(eprojectiles[i].getGlobalBounds().intersects(player.getGlobalBounds()) && fieldState == false){
				eprojectiles.erase(eprojectiles.begin() + i);
				if(health <= 0) // GAME OVER
					go = 0; 
				else
				health--;
			}
		}
		
		

		
		// COLLISION between hearts and player----------------------------------------
		for(size_t i = 0; i < hearts.size(); i++){
			if(hearts[i].getGlobalBounds().intersects(player.getGlobalBounds())){
				hearts.erase(hearts.begin() + i);
				if(health <= 90)
					health += 10;
				else
				health = 100;
			}
		}
		
		
		
		
		// COLLISION between shields and player---------------------------------------
		for(size_t i = 0; i < shields.size(); i++){
			if(shields[i].getGlobalBounds().intersects(player.getGlobalBounds())){
				shields.erase(shields.begin() + i); // remove the shield from the vector
				fieldState = true; // field force is on
				fieldLimit = 0; // set the timer back to zero
			}
		}
		
		
		
		// GAME OVER------------------------------------------------------------------
		for(size_t i = 0; i < enemies.size(); i++){
			if(player.getGlobalBounds().intersects(enemies[i].getGlobalBounds())){
				go = 0;	
			}
		}
		
		if (score <= -50)	
			go = 0;
		
		
		// QUIT the game--------------------------------------------------------------
		if(Keyboard::isKeyPressed(Keyboard::Q) && (go == 2 || go == 5)) 
			go = 0;
			
		
	
			
			
			
		// -------------------------------DRAW----------------------------------------
        window.clear();
        
        window.draw(back);
        
        
        // Draw everything in the GAME------------------------------------------------
        //   CASUAL      DIFFICULT
        if((go == 2) || (go == 5)){
			
			
			// Draw the text on the right side----------------------------------------
			std::string hp = "" + std::to_string(health);
			std::string s = "" + std::to_string(score);
			std::string q = sc + "\n" + s + "\n\n" + "HEALTH\n" + hp;
			text.setString(q);
			window.draw(text);
			
			
			// Draw the hearts--------------------------------------------------------
			for(size_t i = 0; i < hearts.size(); i++){
				window.draw(hearts[i]);
			}
			
			
			// Draw the shields-------------------------------------------------------
			for(size_t i = 0; i < shields.size(); i++){
				window.draw(shields[i]);
			}
			
			
			// Draw the player, it's projectiles and the force field-------------------
			window.draw(player);
			if(fieldState == true && fieldLimit < fieldTime){
				window.draw(field);
				fieldLimit++;
			}
			else if(fieldLimit >= fieldTime)
				fieldState = false;
				
		
			for(size_t i = 0; i < projectiles.size(); i++){
				window.draw(projectiles[i]);
			}
			
			
			// Draw the enemies-------------------------------------------------------
			for(size_t i = 0; i < enemies.size(); i++){
				window.draw(enemies[i]);
			}
			
			
			// Draw enemies' projectiles----------------------------------------------
			for(size_t i = 0; i < eprojectiles.size(); i++){
				window.draw(eprojectiles[i]);
			}
			
		}
		
		
		
		
		
		// Draw the INTRO text--------------------------------------------------------
		else if (go == 1){
			intro.setString(itr);
			window.draw(intro);
			
			if(Keyboard::isKeyPressed(Keyboard::Return))
				go = 3;
			
			else if(Keyboard::isKeyPressed(Keyboard::Escape))
				goto close;
			
		}
		
		
		
		
		
		// Draw the GAME OVER---------------------------------------------------------
		else if (go == 0){
			// Create the game over text
				std::string s = "" + std::to_string(score);
				std::string q = fi + scspace + s + "\n\nPRESS D TO CHANGE DIFFICULTY" + "\nPRESS ENTER TO PLAY AGAIN..." + "\n    PRESS ESC TO EXIT...";
				text.setString(q);
				text.setPosition(width/2-200, heigth/2-90);
				
			// Erase the remaining enemies
			for(size_t i = 0; i < enemies.size(); i++){
				enemies.erase(enemies.begin() + i);
			}
			
			// Erase the remaining hearts
			for(size_t i = 0; i < hearts.size(); i++){
				hearts.erase(hearts.begin() + i);
			}
			
			// Erase the remaining shields
			for(size_t i = 0; i < shields.size(); i++){
				shields.erase(shields.begin() + i);
			}
			
			if(Keyboard::isKeyPressed(Keyboard::Return)){ // option for playing again
				if(back.getTexture() == &background2) // verify the previous game using the set background
					go = 2;
				if(back.getTexture() == &background3)
					go = 5;
				score = 0;
				health = 100;
				text.setPosition(width-115, heigth/2-110);
			}
			
			// Change difficulty level
			if(Keyboard::isKeyPressed(Keyboard::D)){
				go = 4;
				score = 0;
				health = 100;
				text.setPosition(width-115, heigth/2-110);
				back.setTexture(background); // set the menu background
			}
			window.draw(text);
		}
		
		
		
		
		
		// Draw the INSTRUCTIONS------------------------------------------------------
		else if (go == 3){
			// press enter to play
			if(Keyboard::isKeyPressed(Keyboard::Return) && instrdelay >= 5){ 
				go = 4;
				instrdelay = 0;
			}
			else
				instrdelay++;
				
			if(Keyboard::isKeyPressed(Keyboard::Escape))
				goto close;
				
			window.draw(instr);// draw the instructions
			
		}
		
		
		
		//Draw the DIFFICULTY selector------------------------------------------------
		else if (go == 4){
			// press e for easy-------------------------------------------------------
			if(Keyboard::isKeyPressed(Keyboard::Num1) && instrdelay >= 5){ 
				back.setTexture(background2); // set the second background for the easy gameplay
				back.setScale(1.1, 1.1);
				go = 2;
				
			}
			
			
			// press m for medium-----------------------------------------------------
			else if(Keyboard::isKeyPressed(Keyboard::Num2) && instrdelay >= 5){
				back.setTexture(background3);
				go = 5;
				
			}
			
			
			
			else
				instrdelay++;
				
			if(Keyboard::isKeyPressed(Keyboard::Escape))
				goto close;
				
			window.draw(diff);// draw the instructions
		}
		
		
		
		// Exit the game--------------------------------------------------------------
		if(Keyboard::isKeyPressed(Keyboard::Escape)) 
			goto close;
			
		
		//-------------------------------DISPLAY--------------------------------------
        window.display();
    }
    //-------------------------------------------------------------------END OF GAME LOOP------------------------------------------------------
	close:
	window.close();
    return 0;
}
