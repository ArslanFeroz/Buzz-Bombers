
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.

const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid
// int points = 0;  //Storing the scores of the player;
// int level = 1;
// int pre_gen = 0;
// int bee_amount = 0;
// int bee_strike = 0;
// //int fast_bee = 0;
// const int max_combs = 30;
// //int fastBees = 0;
// int max_fastbee = 0;
// const int max_flowers = 20;
// int max_lives = 3;
// const int maxBulletperLevel = 56;
// int leftbullets = maxBulletperLevel;
// const int max_powers = 4;
// const int max_record = 10;


// Vector2f comb_scale(0.9f, 0.9f);
// const int maximumfastbees = 20;

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

void playerMotion(sf::Sprite &player, RenderWindow& window, float &x, float &y, Sprite (&flowers)[], bool (&liveflowers)[], int flowercount, Sprite (&PowerSprite)[], bool (&isActiveSprite)[], int (&power_index)[], bool (&grantPower)[], Vector2f &scale, float (&elapsed_time)[], bool &collision, Clock (&powerClock)[],const int &max_flowers,const int &maximumfastbees, float &move);
void bulletProp(sf::Sprite &sprite, sf::Texture &texture, float, float, bool &, Music &bullet_sound, Music &bgMusic);
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite, Vector2f &scale);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock, int &leftbullets);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void bees(sf::Sprite (&bee)[], int max_bees, int &index, bool (&spawned)[], sf::Texture &texture, RenderWindow& window, sf::Clock &clock, Sprite (&fastbee)[], bool (&Fastspawned)[], Texture &fast_bee_texture, int &fastbeeIndex, int &, int &);
void bee_motion(sf::Sprite (&bee)[], bool(&spawned)[], int index, RenderWindow& window, bool (&moving_right)[], Vector2f bee_velocity, Sprite (&fast_bee)[], bool (&fastSpawned)[], int fastbeeIndex, bool (&fastMoving_right)[], Vector2f fastBee_velocity);
void bee_direction(sf::Sprite (&bee)[], int index, bool (&spawned)[], sf::RenderWindow& window, Sprite (&fast_bee)[], bool (&fastSpawned)[], int fastbeeIndex, int&);
void bee_Collision_bullet(sf::Sprite (&bee)[], bool (&spawned)[], int index, bool &bullet_exist, sf::Sprite bullet, bool (&comb)[], sf::Sprite (&honey_comb)[], Music &strikeSound, Music &bgMusic, bool (&fastSpawn)[], Sprite (&fast_bee)[], int fastbeeIndex, bool (&redcomb_spawn)[], int &bee_strike, int &level, int &leftbullets, int &points);
void honey_combs(sf::Sprite (&honey_comb)[], bool (&comb)[], sf::Texture &texture, sf::Sprite (&bee)[], int index, Vector2f &comb_scale);
void honey_combs_collision(sf::Sprite(&honey_comb)[], bool (&comb)[], int max_combs, sf::Sprite bullet, bool &bullet_exist, Music &obstacleSound, Sprite (&pregen_comb)[], bool (&spawned_pregen)[], Sprite (&red_combs)[], bool (&spawned_redComb)[], int fastbeeIndex, bool (&hit)[], int &level, int &pre_gen, int &leftbullets);
void startMenu(Text (&menu_text)[], RenderWindow &window, int &max_bees, Font &font, bool &start, Vector2f &bee_velocity, Texture &menuTexture, bool (&pregen_comb)[], Music &bgMusic, bool &levelUp, bool &fromMenu, bool (&hiveSpawned)[], Sprite (&bee_hive)[], int &level, int &pre_gen, int &max_fastbee, int &bee_amount, Text (&board)[], bool &pointboard);
void pre_gen_honey_comb(Sprite (&honey_combs)[], Texture &texture, RenderWindow &window, bool (&pregen_comb)[], int &pre_gen, Vector2f &comb_scale);
void collision_player(Sprite &player, Sprite (&bee)[], int bee_index, bool &gameover);
void gameOverMenu(Sprite &gameovertext, RenderWindow &Window, bool &gameover, bool &start, int &level);
void polination(Sprite (&bee)[], bool (&already_spawned)[], int bee_index, RenderWindow &window, Texture flowerTexture, Sprite (&flowers)[], bool (&liveFlower)[], int &flowercount, const int &max_flowers);
void bee_collision_combs(Sprite (&combs)[], Sprite (&pregen_comb)[], Sprite (&bee)[], bool (&spawnBee)[], bool (&spawnComb)[], bool (&spawnPregen)[], int max_combs, bool (&moving_right)[], Sprite (&fast_bee)[], Sprite (&red_comb)[], bool (&spawned_redComb)[], bool (&spawned_fastBee)[], bool (&fastMoving_right)[], int &fastbeeIndex);
void lives(Sprite (&live)[], bool (&spawnedLive)[], Texture &liveTexture, RenderWindow &window, int &counter, bool &gameover, int &max_lives, int &leftbullets, const int &maxBulletperLevel);
void hummingBird(Sprite &bird, RenderWindow &window, Sprite (&honey_comb)[], bool (&spawned_comb)[], bool &bird_exist, float &respawnTime, Sprite (&pregen_combs)[], bool (&spawnedPregen)[], int (&honeyComb_tier)[], int (&pregenComb_tier)[], Sprite (&red_combs)[], bool (&spawned_redComb)[], int (&redComb_tier)[], bool (&hit)[], int &points, int &level, int &max_fastbee, int &bee_amount, int &pre_gen, const int &maximumfastbees);

void collision_bird(Sprite (&bird), Sprite &bulletSprite, bool &bullet_exist, bool &bird_exist, int &birdStrike, int &leftbullets);
void beeHive(Sprite (&bee)[], Sprite (&honey_comb)[], bool (already_spawned)[], bool (&comb)[], RenderWindow &window, Sprite (&bee_hive)[], bool (&hiveSpawned)[], int &bee_amount, const int &max_combs);
void levelUp(bool &levelUp, bool (&already_spawned)[], bool start, int &bee_amount, bool (&fastSpawned)[], int &max_fastbee);
void tiers(Sprite (&pregen_comb)[], bool (&pregenSpawned)[], int (&pregenComb_tier)[], Sprite (&honey_combs)[], bool (&spawnedComb)[], int bee_index, int (&honeyComb_tier)[], Sprite (&red_comb)[], bool (&spawnedRed_comb)[], int (&redComb_tier)[], Sprite (&beeHive)[], bool (&spawnedbee_hive)[], int (&beeHive_tier)[], int &pre_gen, int &level, const int &maximumfastbees);
void beeHive_points(Sprite (&bee_hive)[], bool (&SpawnedHive)[], int (&beeHive_tier)[], int &bee_amount, int &points);

void bonusLives(Sprite (&lives)[], bool (&spawned_live)[], int &points, int &max_lives);
void pregenHives(bool (&hiveSpawned)[], Sprite (&bee_hive)[]);
void powers(Sprite (&PowerSprite)[], Texture &speedInc, Texture &speedDec, Texture &heightInc, Texture &heightDec, RenderWindow &window, bool (&activePowerSprite)[], bool (&hit)[], Sprite (&red_comb)[], int (&power_index)[], bool (&grantPower)[], const int &maximumfastbees);
void powerMove(Sprite (&powerSprite)[], bool (&activePowerSprite)[], RenderWindow &window, float &posi_x, float &posi_y, int index);
void PlayerNameinput(Text &name, Text &inputname, string &playername, RenderWindow &window);
void scoreBoard(Text (&board)[], RenderWindow &window);
void red_honey_combs(Sprite (&red_combs)[], bool (&spawned_redComn)[], Sprite (&fast_bee)[], int &fastbeeIndex, Texture &redComb_texture, Vector2f &comb_scale);

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Declare your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


int main()
{
	srand(static_cast<unsigned>(time(0)));
	int points = 0;  //Storing the scores of the player;
	int level = 1;
	int pre_gen = 0;
	int bee_amount = 0;
	int bee_strike = 0;
	//int fast_bee = 0;
	const int max_combs = 30;
	//int fastBees = 0;
	int max_fastbee = 0;
	const int max_flowers = 20;
	int max_lives = 3;
	const int maxBulletperLevel = 56;
	int leftbullets = maxBulletperLevel;
	const int max_powers = 4;
	const int max_record = 10;


	Vector2f comb_scale(0.9f, 0.9f);
	const int maximumfastbees = 20;


	// Declaring RenderWindow.
	RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(Vector2i(500, 200));
	window.setFramerateLimit(60);

	// Initializing Background Music.
	Music bgMusic;
	bgMusic.openFromFile("Music/Forest.ogg");
	bgMusic.setLoop(true);
	bgMusic.play();
	bgMusic.setVolume(50);

	Music Bullet_sound;
	Bullet_sound.openFromFile("Sound Effects/fire.wav");
	Bullet_sound.setVolume(50);

	Music strikeSound;
	strikeSound.openFromFile("Sound Effects/hit.wav");
	strikeSound.setVolume(50);

	Music obstacleSound;
	obstacleSound.openFromFile("Sound Effects/Obstacle.wav");

	// Initializing Player and Player Sprites.
	float player_x = (gameRows / 2) * boxPixelsX;
	float player_y = (gameColumns - 4) * boxPixelsY;
	
	Texture playerTexture;
	Sprite playerSprite;
	Vector2f scale(1.f, 1.f);
	float move = 10.f;
	playerTexture.loadFromFile("Textures/spray.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(scale);
	//	playerSprite.setTextureRect(IntRect(0, 0, boxPixelsX, boxPixelsY));

		// Initializing Bullet and Bullet Sprites
		// Data for bullet / Spray pellet
    Texture bulletTexture;
	Sprite bulletSprite;
	float bullet_x = player_x;
	float bullet_y = player_y;
	bool bullet_exists = true;
	
	//Creating bees
	int max_bees = 50;
	int bee_index = 0;

	bool already_spawned[max_bees]={false};  //It will check if the bee is spawned or not
	Sprite bee[max_bees];
	bool right_motion[max_bees] = {true};

	Vector2f bee_velocity(3.f, 0.f);
	Texture bee_texture;
	bee_texture.loadFromFile("Textures/Regular_bee.png");

	//Fast bees 
	Sprite fast_bee[maximumfastbees];
	bool Fast_spawned[maximumfastbees] = {false};
	int fastbeeIndex = 0;
	Texture fast_bee_texture;
	fast_bee_texture.loadFromFile("Textures/Fast_bee.png");
	bool fastMoving_right[maximumfastbees] = {true};
	Vector2f fastBee_velocity(5.f, 0.f);
	
	//HoneyCombs
	sf::Sprite honey_comb[max_bees];
	bool spawned_comb[max_bees]={false};
	int honeyComb_tier[max_bees] = {0};

	//Red honey Combs
	Sprite red_combs[maximumfastbees];
	bool spawned_redComb[maximumfastbees] = {false};
	Texture redComb_texture;
	redComb_texture.loadFromFile("Textures/honeycomb_red.png");
	int redComb_tier[maximumfastbees] = {0};

	//Beehive
	Sprite bee_hive[max_bees];
	bool hiveSpawned[max_bees] = {false};
	Texture hiveTexture;
	hiveTexture.loadFromFile("Textures/hive.png");
	if(!hiveTexture.loadFromFile("Textures/hive.png"))
		cout<<"Hive texture not loaded"<<endl;
	//Applying texture
	for(int i=0; i<max_bees; i++){
		bee_hive[i].setTexture(hiveTexture);
	}
	int beeHive_tier[max_bees] = {0};
	
	
	Clock spawn_clock;
	
	Texture comb_texture;
	comb_texture.loadFromFile("Textures/honeycomb.png");

	//Pregenerated honeycombs
	Sprite pre_gen_comb[15];
	bool spawned_pre_gen_comb[15] = {false};
	int pregenComb_tier[15] = {0};

	//Pollination flowers
	Sprite flowers[max_flowers];
	bool liveflowers[max_flowers] = {false};
	Texture flowerTexture;
	flowerTexture.loadFromFile("Textures/obstacles.png");
	if(!flowerTexture.loadFromFile("Textures/obstacles.png")){
		cout<<"Hive texture not loaded"<<endl;
	}
	for(int i=0; i<max_flowers; i++){

		flowers[i].setTexture(flowerTexture);
	}
	int flowercount = 0;

	//Lives of the player
	const int maximunNumberoflives = 10;
	Sprite live[maximunNumberoflives];
	bool spawnedlive[maximunNumberoflives] = {false};
	Texture liveTexture;
	liveTexture.loadFromFile("Textures/spray.png");
	if(!liveTexture.loadFromFile("Textures/spray.png")){
			cout<<"Texture not loaded"<<endl;
	}
	int counter = 1;  //if counter exceed maxlives then the game will be over

	//Left Bullet textbox;
	Font font;
	font.loadFromFile("Textures/arcade.ttf");
	Text leftBulletText;
	leftBulletText.setFont(font);
	leftBulletText.setCharacterSize(32);
	leftBulletText.setFillColor(Color::Black);
	leftBulletText.setPosition(resolutionX/2 - 200, resolutionY - 60);
        
        

	Clock bulletClock;
	
	// The ground on which player moves
	RectangleShape groundRectangle(Vector2f(960, 64));
	groundRectangle.setPosition(0, (gameColumns - 2) * boxPixelsY);
	groundRectangle.setFillColor(Color::Green);

	//Scores text
	Text score;
	score.setFont(font);
	score.setCharacterSize(32);
	score.setFillColor(Color:: Black);
	score.setPosition(0, 600);

	//Humming bird
	Clock birdclock;
	Texture bird_texture;
	bird_texture.loadFromFile("Textures/bird.png");
	bool bird_exist = true;
	int birdStrike = 0;
	float respawnTime = 0.f;

	IntRect rectSource(0, 0, 32, 32);
	Sprite bird;
	bird.setTexture(bird_texture);
	bird.setTextureRect(rectSource);
	bird.setColor(Color::Blue);
	bird.setPosition(static_cast<float>(rand()%900), static_cast<float>(rand()%520));
	bird.setScale(1.5, 1.5);

	//Menu
	Text menu_text[4];
	for(int i=0; i<4; i++){
		menu_text[i].setFont(font);
		menu_text[i].setCharacterSize(32);
		menu_text[i].setFillColor(Color::Green);
	}
	Texture menuTexture;
	menuTexture.loadFromFile("Textures/buzzBombers.png");
	bool fromMenu = false;

	//Level won Texture
	Texture congrats;
	congrats.loadFromFile("Textures/congrats.png");
	if(!congrats.loadFromFile("Textures/congrats.png")){
		cout<<"Congrats texture failed."<<endl;
		exit(0);
	}
	Sprite youWon;
	youWon.setTexture(congrats);
	//youWon.setPosition(resolutionX/2 - youWon.getTextureRect().width, resolutionY/2 - youWon.getTextureRect().height);
	//Determining the scale to cover the complete window
	float youWon_x = resolutionX / congrats.getSize().x;
	float youWon_y = resolutionY / congrats.getSize().y;
	youWon.setScale(youWon_x, youWon_y);

	//End game texture (when all three levels are complete)
	Texture endgame;
	endgame.loadFromFile("Textures/end.png");
	Sprite end;
	end.setTexture(endgame);
	float end_x = resolutionX / endgame.getSize().x;
	float end_y = resolutionY / endgame.getSize().y;
	//end.setScale(end_x, end_y);

	//End game Music
	Music endMusic;
	endMusic.openFromFile("Sound Effects/endMusic.wav");
	endMusic.setVolume(50);


	bool start = true;

	//Game Over
	// Text gameovertext;
	// gameovertext.setFont(font);
	// gameovertext.setString("GAME OVER");
	// gameovertext.setCharacterSize(56);
	// gameovertext.setFillColor(Color::Green);
	// gameovertext.setPosition(resolutionX/2, resolutionY/2);
	Texture gameoverTexture;
	gameoverTexture.loadFromFile("Textures/gameOverText.png");
	Sprite gameoverSprite;
	gameoverSprite.setTexture(gameoverTexture);
	float over_x = resolutionX / gameoverTexture.getSize().x;
	float over_y = resolutionY / gameoverTexture.getSize().y;
	gameoverSprite.setScale(over_x, over_y);
	bool gameover = false;

	//Game over Music
	Music gameoverMusic;
	gameoverMusic.openFromFile("Sound Effects/gameoverMusic.mp3");
	if(!gameoverMusic.openFromFile("Sound Effects/gameoverMusic.mp3")){
		cout<<"Error opening game over texture "<<endl;
		exit(0);
	}
	gameoverMusic.setVolume(50);

	bool levelup = false;

	//Test sprite
	Sprite testSprite;
	testSprite.setTexture(flowerTexture);
	testSprite.setPosition(100.f, 100.f);
	
	//POWERS
	int power_index[maximumfastbees] = {0};
	bool grantPower[max_powers] = {false};
	Sprite powerSprite[maximumfastbees];
	bool activePowerSprite[maximumfastbees] = {false};
	bool hit[maximumfastbees] = {false};
	float elapsed_time[max_powers] = {0.f};
	bool powerCollision = false;
	Clock powerClock[max_powers];

	//Taking name input from the user
	Text name;
	name.setFont(font);
	name.setCharacterSize(40);
	name.setString("Enter Name ");
	name.setFillColor(Color :: Green);
	name.setPosition(resolutionX/2 - 100, resolutionY/2 - 100);


	Text inputname;
	inputname.setFont(font);
	inputname.setCharacterSize(40);
	inputname.setString("");
	inputname.setFillColor(Color :: Green);
	inputname.setPosition(resolutionX/2 - 100, resolutionY/2 );
	fstream myfile;

	string playerName;
	int Point[max_record];
	string Name[max_record];
	bool pointboard = false;




	//Textures for powers
	Texture speedInc;
	Texture speedDec;
	Texture heightInc;
	Texture heightDec;

	speedInc.loadFromFile("Sprites/Speed_Inc.png");
	speedDec.loadFromFile("Sprites/Speed_Dec.png");
	heightInc.loadFromFile("Sprites/Height_Inc.png");
	heightDec.loadFromFile("Sprites/Height_Dec.png");

	//Score Board
	Text board[12];
	for(int i=0; i<12; i++){


		if(i==0 || i==11){
			board[i].setFillColor(Color::Green);
		}
		else{

			board[i].setFillColor(Color::Red);
		}
			

		
		board[i].setFont(font);
		board[i].setCharacterSize(35);
		board[i].setPosition(150.f,  50 + i * 50);
	}
	


	while (window.isOpen()){

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				//return 0;
				exit(0);
			}
			// else if (e.type == Event::KeyPressed){
			//         if(e.key.code == sf::Keyboard::Enter)
			//                 window.close();
			// }
		}

		//Creating the menu
		if(start){
			
			//Creating a Simple menu for now
			startMenu(menu_text,window, max_bees, font, start, bee_velocity, menuTexture, spawned_pre_gen_comb, bgMusic, levelup, fromMenu, hiveSpawned, bee_hive, level, pre_gen, max_fastbee, bee_amount, board, pointboard);
			
		}

		//Showing the board menu
		if(pointboard){
			scoreBoard(board, window);
			pointboard = false;
			startMenu(menu_text,window, max_bees, font, start, bee_velocity, menuTexture, spawned_pre_gen_comb, bgMusic, levelup, fromMenu, hiveSpawned, bee_hive, level, pre_gen, max_fastbee, bee_amount, board, pointboard);


		}
		
		
		//Creating the bird animation
		if(birdclock.getElapsedTime().asSeconds() >= 0.5f){
			//Moving to the next frame
			rectSource.left+=32;
			if(rectSource.left == 64){
				//Resetting the frame to 0 when the end of the image which is 64pixel is reached
				rectSource.left = 0;
			}
		
			
			//Updating the texture of the bird
			bird.setTextureRect(rectSource);
			//Restarting the clock
			birdclock.restart();
		}

		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Function Here. Some have been written for you.  //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			bulletProp( bulletSprite, bulletTexture ,bullet_x, bullet_y, bullet_exists, Bullet_sound, bgMusic);
			bullet_exists = true;
		}
		
		playerMotion(playerSprite, window, player_x, player_y, flowers, liveflowers, flowercount, powerSprite, activePowerSprite, power_index, grantPower, scale, elapsed_time, powerCollision, powerClock, max_flowers, maximumfastbees, move);
		
		//Getting bees
		bees(bee, max_bees, bee_index, already_spawned, bee_texture, window, spawn_clock, fast_bee, Fast_spawned, fast_bee_texture, fastbeeIndex, level, max_fastbee);
		
		//Moving the bees
		bee_motion(bee, already_spawned, bee_index, window, right_motion, bee_velocity, fast_bee, Fast_spawned, fastbeeIndex, fastMoving_right, fastBee_velocity);
 
		//checking the collision of bees with combs
		bee_collision_combs(honey_comb, pre_gen_comb, bee, already_spawned, spawned_comb, spawned_pre_gen_comb, max_combs, right_motion, fast_bee, red_combs, spawned_redComb, Fast_spawned, fastMoving_right, fastbeeIndex);
		
		//Moving the bees down when they encounter the right edge
		bee_direction(bee, bee_index, already_spawned, window, fast_bee, Fast_spawned, fastbeeIndex, level);
		
		//Checking for collision with the bullet
		bee_Collision_bullet(bee, already_spawned,bee_index, bullet_exists, bulletSprite, spawned_comb, honey_comb, strikeSound, bgMusic, Fast_spawned, fast_bee, fastbeeIndex, spawned_redComb, bee_strike, level, leftbullets, points);

		//Pre generated honeyCombs
		pre_gen_honey_comb(pre_gen_comb, comb_texture, window, spawned_pre_gen_comb, pre_gen, comb_scale);

		//Red Honey Combs
		red_honey_combs(red_combs, spawned_redComb, fast_bee, fastbeeIndex, redComb_texture, comb_scale);
		
		//Drawing the honeyCombs
		honey_combs(honey_comb, spawned_comb, comb_texture, bee, bee_index, comb_scale);

		//Checking for the collision of honey combs and bullets
	    honey_combs_collision(honey_comb, spawned_comb, bee_index, bulletSprite, bullet_exists, obstacleSound, pre_gen_comb, spawned_pre_gen_comb, red_combs, spawned_redComb, fastbeeIndex, hit, level, pre_gen, leftbullets);

		//Removing the bees when they reach the lower right edge
		polination(bee, already_spawned, bee_index, window, flowerTexture, flowers, liveflowers, flowercount, max_flowers);

		//Showing the lives of the player
		lives(live, spawnedlive, liveTexture, window, counter, gameover, max_lives, leftbullets, maxBulletperLevel);

		//Moving the humming bird
		hummingBird(bird, window, honey_comb, spawned_comb, bird_exist, respawnTime, pre_gen_comb, spawned_pre_gen_comb, honeyComb_tier, pregenComb_tier, red_combs, spawned_redComb, redComb_tier, hit, points, level, max_fastbee, bee_amount, pre_gen, maximumfastbees);

		//Checking collision of bird with bullet
		collision_bird(bird, bulletSprite, bullet_exists, bird_exist, birdStrike, leftbullets);

		levelUp(levelup, already_spawned, start, bee_amount, Fast_spawned, max_fastbee);

		//BeeHive
		//void beeHive(Sprite (&bee)[], Sprite (&honey_comb)[], bool (already_spawned)[], bool (&comb)[], RenderWindow &window) 
		beeHive(bee, honey_comb, already_spawned, spawned_comb, window, bee_hive, hiveSpawned, bee_amount, max_combs);

		//void collision_player(Sprite &player, Sprite (&bee)[], int bee_index, bool &gameover);
		collision_player(playerSprite, fast_bee, fastbeeIndex, gameover);

		//Determining the tiers
		tiers(pre_gen_comb, spawned_pre_gen_comb, pregenComb_tier, honey_comb, spawned_comb, bee_index, honeyComb_tier, red_combs, spawned_redComb, redComb_tier, bee_hive, hiveSpawned, beeHive_tier, pre_gen, level, maximumfastbees);

		//Assigning points with  respect to bee hives
		beeHive_points(bee_hive, hiveSpawned, beeHive_tier, bee_amount, points);

		//Bonus lives
		bonusLives(live, spawnedlive, points, max_lives);

		//powers
		powers(powerSprite, speedInc, speedDec, heightInc, heightDec, window, activePowerSprite, hit, red_combs, power_index, grantPower, maximumfastbees);

		

		

		//If the player dies then Restart the game

		//If the flowers/obstacles reach 19 then end the games
		if(flowercount == 19)
			gameover = true;

		
		
		
		if(gameover){

			bgMusic.stop();
			gameoverMusic.play();
			
			
			//If the game is over then resetting all the sprites and points;
			bee_index = 0;
				if(level!=1){
					fastbeeIndex = 0;
					for(int i=0; i<max_fastbee; i++){
						Fast_spawned[i] = false;
						spawned_redComb[i] = false;
					}

					//Resetting the speed and scale of the player if it was the boss level
					move = 10.f;
					scale.y = 1.f;
				}
				//Resetting all the variables and arrays
				for(int i=0; i<15; i++){
					spawned_pre_gen_comb[i] = false;
				}
				for (int i = 0; i < max_bees; ++i) {
					spawned_comb[i] = false;
					already_spawned[i] = false;
				}
				//Resetting the hives if they exist
				for(int i=0; i<max_bees; i++){
					
					hiveSpawned[i] = false;

				}
				//Removing the flowers
				for(int i=0; i<max_flowers; i++){
					liveflowers[i] = false;
	
				}
				flowercount = 0;

				//Removing all the powers
				for(int i=0; i<maximumfastbees; i++){
					activePowerSprite[i] = false;
					hit[i] = false;
					power_index[i] = 0;
				}
				for(int i=0; i<max_powers; i++){
					grantPower[i] = false;
				}

				//Resetting lives and counter
				leftbullets = maxBulletperLevel;
				counter = 1;
				max_lives = 3;
				for(int i=0; i<max_lives; i++){
					spawnedlive[i] = true;
				}
				
				level = 1;
				
				bee_strike = 0;
				start = true;
				gameover = false;
				//window.clear();
				//startMenu(menu_text,window, max_bees, font, start, bee_velocity, menuTexture, spawned_pre_gen_comb);
				gameOverMenu(gameoverSprite, window, gameover, start, level);
				PlayerNameinput(name, inputname, playerName, window);
				

				//Adding data to the file
				/* **********************************************************************************8*/

				/*
					I am doing the following steps to add records to the file
					1. Open the file and retreive all the data into two arrys. Names go into name array and points go into points array.
					2. Then sort those array in descending order.
					3. After sorting , Compare the lowest point value with the current points.
					4. If greater then swap them.
					5. Then resort the arrays in descending order.
					6. Now open the file in write mode(clearing all the previous data), fill the file with the data from the two arrays
				*/


				
				myfile.open("record.txt", ios::in);

				//openning the file and retrieving previous data
				while(myfile.is_open()){

					for(int i=0; i<max_record; i++){
						myfile>>Name[i]>>Point[i];
					}

					myfile.close();
				}

				//Sorting the data in descending order
				for(int i=0; i<9; i++){

					for(int j=i+1; j<10; j++){

						if(Point[i] < Point[j]){
							// swap(Point[i], Point[j]);
								// swap(Name[i], Name[j]);

								int temp = Point[i];
								Point[i] = Point[j];
								Point [j] = temp;

								string tempo = Name[i];
								Name[i] = Name[j];
								Name[j] = tempo;
						}
							
					}
				}

				//Comparing the loweset value data with the points 
				if(points > Point[max_record - 1]){
					Point[max_record - 1] = points;
					Name[max_record - 1] = playerName;
				}

				//Resorting
				for(int i=0; i<max_record - 1; i++){

					for(int j=i+1; j<max_record; j++){

						if(Point[i] < Point[j]){
							// swap(Point[i], Point[j]);
								// swap(Name[i], Name[j]);

								int temp = Point[i];
								Point[i] = Point[j];
								Point [j] = temp;

								string tempo = Name[i];
								Name[i] = Name[j];
								Name[j] = tempo;
						}
							
					}
				}


				//Writing data to the file
				myfile.open("record.txt", ios::out);
				while(myfile.is_open()){

					for(int i=0; i<max_record; i++){

						myfile << Name[i] <<" "<<Point[i]<<'\n';
					}
					myfile.close();
				}

				playerName = "";

				/****************************************************************************************** */


				points = 0;				
				gameoverMusic.stop();
				bgMusic.play();
				continue;
		}

		
		
			// If level up then resetting all the sprites
			if(levelup){
				
				if(!fromMenu)
					level += 1;

				bgMusic.play();
				bgMusic.setVolume(50);

				//SHowing the end window if all 3 levels are complete
				if(level > 4 || fromMenu){

					if(level == 4){
						level+=1;
						points = 0;

					}

					//Resetting the speed and scale of the player if it was the boss level
					move = 10.f;
					scale.y = 1.f;
					
						
					fromMenu = false;
					bgMusic.stop();
					endMusic.play();
					Clock mid;
					float elapsed_time = 0.f;
					while(elapsed_time < 7.f){

						window.clear();
						window.draw(end);
						window.display();
						elapsed_time+=mid.restart().asSeconds();
					}
					endMusic.stop();
					PlayerNameinput(name, inputname, playerName, window);
					
					bgMusic.play();
					//Adding data to the file
				/* **********************************************************************************8*/

					
					myfile.open("record.txt", ios::in);

					//Retrieving
					while(myfile.is_open()){

						for(int i=0; i<max_record; i++){
							myfile>>Name[i]>>Point[i];
						}

						myfile.close();
					}

					//Sorting
					for(int i=0; i<9; i++){

						for(int j=i+1; j<10; j++){

							if(Point[i] < Point[j]){
								// swap(Point[i], Point[j]);
								// swap(Name[i], Name[j]);

								int temp = Point[i];
								Point[i] = Point[j];
								Point [j] = temp;

								string tempo = Name[i];
								Name[i] = Name[j];
								Name[j] = tempo;
							}
								
						}
					}

					//Comparing
					if(points > Point[max_record - 1]){
						Point[max_record - 1] = points;
						Name[max_record - 1] = playerName;
					}

					//Sorting
					for(int i=0; i<max_record - 1; i++){

						for(int j=i+1; j<max_record; j++){

							if(Point[i] < Point[j]){
								// swap(Point[i], Point[j]);
								// swap(Name[i], Name[j]);

								int temp = Point[i];
								Point[i] = Point[j];
								Point [j] = temp;

								string tempo = Name[i];
								Name[i] = Name[j];
								Name[j] = tempo;
							}
								
						}
					}

					//Writing 
					myfile.open("record.txt", ios::out);
					while(myfile.is_open()){

						for(int i=0; i<max_record; i++){

							myfile << Name[i] <<" "<<Point[i]<<'\n';
						}
						myfile.close();
					}

					//Emptying the string
					playerName = "";

				/****************************************************************************************** */


				}

				//cout<<"Inside the striker";
				bee_index = 0;
				if(level!=1){
					fastbeeIndex = 0;
					for(int i=0; i<max_fastbee; i++){
						Fast_spawned[i] = false;
						spawned_redComb[i] = false;
					}
				}
				//Resetting all the variables and arrays
				for(int i=0; i<15; i++){
					spawned_pre_gen_comb[i] = false;
				}
				for (int i = 0; i < max_bees; ++i){
					spawned_comb[i] = false;
					already_spawned[i] = false;
				}
				//Resetting the hives if they exist
				for(int i=0; i<max_bees; i++){
					
					hiveSpawned[i] = false;

				}
				//Removing the flowers
				for(int i=0; i<max_flowers; i++){
					liveflowers[i] = false;
	
				}
				flowercount = 0;
				
				
				
				if(level <= 3){
					//Showing the congrats texture
					Clock mid;
					float elapsed_time = 0.f;
					while(elapsed_time < 3.f){

						window.clear();
						window.draw(youWon);
						window.display();
						elapsed_time+=mid.restart().asSeconds();
					}


				}
				
				//Removing all the powers
				for(int i=0; i<maximumfastbees; i++){
					activePowerSprite[i] = false;
					hit[i] = false;
					power_index[i] = 0;
				}

				for(int i=0; i<max_powers; i++){
					grantPower[i] = false;
				}

				if(level > 4){

					max_lives = 3;
					//Resetting the lives
					for(int i=0; i<max_lives; i++){
						spawnedlive[i] = true;
					}
					leftbullets = maxBulletperLevel;
					counter = 1;
					level = 1;
					points = 0;

				}
					

				
				levelup = false;
				start = true;
				//window.clear();
				startMenu(menu_text,window, max_bees, font, start, bee_velocity, menuTexture, spawned_pre_gen_comb, bgMusic, levelup, fromMenu, hiveSpawned, bee_hive, level, pre_gen, max_fastbee, bee_amount, board, pointboard);
				continue;
			}
		
		
		
		
		//Updating the scor3e and left bullets text display
		score.setString(to_string(points));
		leftBulletText.setString( "Left Sprays " + to_string(leftbullets));
	    	

		//Playing the background music
		if(Bullet_sound.getStatus() == SoundSource::Stopped){
			bgMusic.setVolume(50);
		}

		if(strikeSound.getStatus() == SoundSource::Stopped){
			bgMusic.setVolume(50);
		}	
        window.clear();
		if (bullet_exists == true)
		{
		
			moveBullet(bullet_y, bullet_exists, bulletClock, leftbullets);
			drawBullet(window, bullet_x, bullet_y, bulletSprite);
			//bgMusic.pause();
			//Bullet_sound.play();
		}
		else
		{
			//Bullet_sound.pause();
			//bgMusic.play();
			bullet_x = player_x;
			bullet_y = player_y;
		}
		//Drawing the bees
		for(int i=0; i<max_bees; i++){
                        if(already_spawned[i]){
                            window.draw(bee[i]);
                        }
                        //Drawing the honey Combs
                        if(spawned_comb[i]){
                            window.draw(honey_comb[i]);
                        }
                }
		

		//Drawing the pregenerated honeycombs
		for(int i=0; i<pre_gen; i++){
			if(spawned_pre_gen_comb[i]){

				//cout<<"honey COmb"<<endl;
				window.draw(pre_gen_comb[i]);
			}
		}

		//Drawing the fast bees
		if(level!=1){
			for(int i=0; i<max_fastbee; i++){
				if(Fast_spawned[i]){
					window.draw(fast_bee[i]);
				}

				if(spawned_redComb[i]){
					
					// if(!red_combs[i].getTexture()){
					// 	red_combs[i].setTexture(redComb_texture);
					// 	red_combs[i].setScale(comb_scale);
					// 	red_combs[i].setPosition(fast_bee[i].getPosition().x, fast_bee[i].getPosition().y);
					// }
					

					window.draw(red_combs[i]);
				}
				
				
			}

			
		}
		//Drawing bee hives
		for(int i=0; i<max_bees; i++){

			if(hiveSpawned[i]){
				window.draw(bee_hive[i]);
			}
		}
		//The ground on which the player moves
		window.draw(groundRectangle);


		//Drawing the flowers
		for(int i=0; i<max_flowers; i++){
			
			if(liveflowers[i]){

				window.draw(flowers[i]);
			}
		}

		
		//Drawing the lives of the players
		for(int i=0; i<max_lives; i++){

			if(spawnedlive[i]){

				
				window.draw(live[i]);
			}
		}

		//Drawing the power sprites
		for(int i=0; i<maximumfastbees; i++){

			if(activePowerSprite[i]){

				//Moving it down
				//getting positions
				float posi_x = powerSprite[i].getPosition().x;
				float posi_y = powerSprite[i].getPosition().y;

				powerMove(powerSprite, activePowerSprite, window, posi_x, posi_y, i);

				window.draw(powerSprite[i]);
			}
		}

	
		

		

		drawPlayer(window, player_x, player_y, playerSprite, scale);
		//Drawing the bird if it exists
		if(bird_exist){

			respawnTime = 0.f;
			window.draw(bird);
		}
		
		window.draw(testSprite);
		window.draw(score);
		window.draw(leftBulletText);
		window.display();


		

		
	}
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite, Vector2f &scale) {
	playerSprite.setScale(scale);
	playerSprite.setPosition(player_x, player_y);
	window.draw(playerSprite);
}

void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock, int &leftbullets) {
	//if (bulletClock.getElapsedTime().asMilliseconds() < 20)
	//	return;

	//bulletClock.restart();
	bullet_y -= 12;
	if (bullet_y < -32){
		leftbullets -= 1;
		bullet_exists = false;

	}
		
}
void drawBullet(sf::RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite) {
	bulletSprite.setPosition(bullet_x, bullet_y);
	window.draw(bulletSprite);
}
void bulletProp(sf::Sprite &sprite, sf::Texture &texture,float x, float y, bool &exist, Music &bullet_sound, Music &bgMusic){
        
	texture.loadFromFile("Textures/bullet.png");
	sprite.setTexture(texture);
	sprite.setScale(3, 3);
    sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	sprite.setPosition(x, y);
	exist = true;
	if(exist){
		
			bgMusic.setVolume(0);
			bullet_sound.play();

	}

	
}


void playerMotion(sf::Sprite &player, RenderWindow& window, float &x, float &y, Sprite (&flowers)[], bool (&liveflowers)[], int flowercount, Sprite (&PowerSprite)[], bool (&isActiveSprite)[], int (&power_index)[], bool (&grantPower)[], Vector2f &scale, float (&elapsed_time)[], bool &collision, Clock (&powerClock)[], const int &max_flowers, const int &maximumfastbees, float &move){
        
				

				if(flowercount == 0){
					if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x>0  ){
						//player.move(-5.f, 0.f);
						x-=move;
					}
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x< (window.getSize().x - player.getTextureRect().width) ){
								//player.move(5.f, 0.f);
								x+=move;	                
					}

				}

				else{

					bool rightMove, leftMove;

					for(int i=0; i<max_flowers; i++){

							
							if(liveflowers[i]){

								//flower coordinates
								Vector2f flower_coordinates(flowers[i].getPosition().x, flowers[i].getPosition().y);

								//Player coordinates
								//Vector2f player_coordinates(player.getPosition());

								if(x + player.getTextureRect().width >= flower_coordinates.x && x <= flowers[i].getTextureRect().width + flower_coordinates.x){

									leftMove = true;
									rightMove = false;
								}
								// else if(player_coordinates.x < flower_coordinates.x + flowers[i].getTextureRect().width && player_coordinates.x + player.getTextureRect().width > flower_coordinates.x + flowers[i].getTextureRect().width){

								// 	leftMove = false;
								// 	rightMove = true;
								// }
								else if(x < flowers[i].getTextureRect().width + 10){
									leftMove = false;
									rightMove = true;
								}
								
								else{
									rightMove = true;
									leftMove = true;
								}
								


							}


					}

					if(sf::Keyboard::isKeyPressed(Keyboard::Left)){

						if(leftMove){

							x-=10;
						}
					}
					else if(sf::Keyboard::isKeyPressed(Keyboard::Right)){
						
						if(rightMove){

							x+=10;
						}
					}
					
				}

				//Checking the player collision with the power

				//Clock
				//the Power will be active for max 10seconds
				//static Clock powerClock[max_powers];
				
				for(int i=0; i<maximumfastbees; i++){


					//static bool collision = false;
					if(isActiveSprite[i]){

						//getting positions
						float player_x = player.getPosition().x;
						float player_y = player.getPosition().y;
						float power_x = PowerSprite[i].getPosition().x;
						float power_y = PowerSprite[i].getPosition().y;

						//checking collision
						// if(player_x < power_x + PowerSprite[i].getTextureRect().width &&  player_x + player.getTextureRect().width > power_x &&
						//   player_y < power_y + PowerSprite[i].getTextureRect().height && player_y + player.getTextureRect().height > power_y){

						// 	collision = true;
						// 	isActiveSprite[i] = false;
						// }

						//Collision logic not working using global bounds for now
						if(player.getGlobalBounds().intersects(PowerSprite[i].getGlobalBounds())){
							//collision = true;
							isActiveSprite[i] = false;
							grantPower[power_index[i]- 1] = true;
						}

						


						
							
					}

					// switch (power_index[i])
					// 	{
					// 		case 1: move = 20.f;
					// 				break;
					// 		case 2: move = 2.f;
					// 				break;
					// 		case 3: scale.y = 1.3f;
					// 				break;
					// 		case 4: scale.y = 0.7f;
					// 				break;
					// 		case 5: move = 10.f;
					// 				break;
					// 		case 6: scale.y = 1.f;
					// 				break;
					// 	}

					if(grantPower[0]){
							//elapsed_time[0] += powerClock[0].restart().asSeconds();
							move = 20.f;
							//power_index[i] = 1;
							//cout<<"Elapsed Time Speed up "<<elapsed_time[0]<<endl;

						}
							
						
						if(grantPower[1]){
							//elapsed_time[1] += powerClock[1].restart().asSeconds();
							//power_index[i] = 2;
							move = 2.f;
							//cout<<"Elapsed Time Speed down "<<elapsed_time[1]<<endl;

						}
							
						
						if(grantPower[2]){
							//elapsed_time[2] += powerClock[2].restart().asSeconds();
							//power_index[i] = 3;
							scale.y = 1.3f;
							//cout<<"Elapsed Time height up "<<elapsed_time[2]<<endl;

						}
							
						
						if(grantPower[3]){
							//elapsed_time[3] += powerClock[3].restart().asSeconds();
							//power_index[i] = 4;
							scale.y = 0.7f;
							//cout<<"Elapsed Time height down "<<elapsed_time[3]<<endl;

						}
								

					if(grantPower[0] && grantPower[1]){
							//I am selecting index 5, as the index which means normal speed of the player
							//power_index[i] = 5;
							move = 10.f;
							//elapsed_time[0] = elapsed_time[1] = 0.f;
							grantPower[0] = grantPower[1] = false;

						}
					if(grantPower[2] && grantPower[3]){
							scale.y = 1.f;
							
							//power_index[i] = 6;
							//elapsed_time[2] = elapsed_time[3] = false;
							grantPower[2] = grantPower[3] = false;
						}
						



						



					// //Removing the  effect of power after 10 sec
					// 	if(elapsed_time[0] >= 5){
					// 		//move = 10.f;
					// 		grantPower[0] = false;
					// 		elapsed_time[0] = 0;
					// 		// cout<<"Elapsed time of speed up set to "<<elapsed_time[0]<<endl;
					// 		// cout<<"gran Power of speed up set to"<<grantPower[0]<<endl;
					// 		power_index[i] = 5;
					// 	}

					// 	if(elapsed_time[1] >= 5){
					// 		//move = 10.f;
					// 		grantPower[1] = false;
					// 		elapsed_time[1] = 0;
					// 		// cout<<"Elapsed time of speed down set to "<<elapsed_time[1]<<endl;
					// 		// cout<<"gran Power of speed down set to"<<grantPower[1]<<endl;
							
					// 		power_index[i] = 5;
					// 	}

					// 	if(elapsed_time[2] >= 5){
					// 		//scale.y = 1.f;
							
					// 		grantPower[2] = false;
					// 		elapsed_time[2] = 0;
					// 		// cout<<"Elapsed time of height up set to "<<elapsed_time[2]<<endl;
					// 		// cout<<"gran Power of height up set to"<<grantPower[2]<<endl;
							
					// 		power_index[i] = 6;
					// 	}
							
					// 	if(elapsed_time[3] >= 5){
					// 		//scale.y = 1.f;
							
					// 		grantPower[3] = false;
					// 		elapsed_time[3] = 0;
					// 		// cout<<"Elapsed time of height down set to "<<elapsed_time[3]<<endl;
					// 		// cout<<"gran Power of height down set to"<<grantPower[3]<<endl;
							
					// 		power_index[i] = 6;
					// 	}
						
						
				}

				
				

}


void bees(sf::Sprite (&bee)[], int max_bees, int &index, bool (&spawned)[], sf::Texture &texture, RenderWindow& window, sf::Clock &clock, Sprite (&fastbee)[], bool (&Fastspawned)[], Texture &fast_bee_texture, int &fastbeeIndex, int &level, int &max_fastbee) {
    static float spawn_time = 1.f; 
    static float elapsed_time = 0.f; 
    sf::Time deltaTime = clock.restart(); 
    elapsed_time += deltaTime.asSeconds(); 

    if (elapsed_time >= spawn_time && index < max_bees) {
        
        bee[index].setTexture(texture); 
        bee[index].setPosition(
            static_cast<float>(rand() % (window.getSize().x - static_cast<int>(bee[index].getTextureRect().width))), 
            static_cast<float>(rand() % 100) 
        );

        spawned[index] = true; // Mark this bee as spawned
        elapsed_time = 0.f; 
        index++; 
    }

	Clock fastclock;
	float fast_spawn_time = 0.f;
	fast_spawn_time += fastclock.restart().asSeconds();

	//Spawning fast bees
	if(level!=1){
		if (fastbeeIndex < max_fastbee && !Fastspawned[fastbeeIndex]){
        
				fastbee[fastbeeIndex].setTexture(fast_bee_texture); 
				fastbee[fastbeeIndex].setPosition(
					static_cast<float>(rand() % (window.getSize().x - static_cast<int>(fastbee[fastbeeIndex].getTextureRect().width))), 
					static_cast<float>(rand() % 100) 
				);

				Fastspawned[fastbeeIndex] = true; // Mark this bee as spawned
				//fast_spawn_time = 0.f; 
				fastbeeIndex++; 
    	}
	}
	

}

void bee_motion(sf::Sprite (&bee)[], bool(&spawned)[], int index, RenderWindow& window, bool (&moving_right)[], Vector2f bee_velocity, Sprite (&fast_bee)[], bool (&fastSpawned)[], int fastbeeIndex, bool (&fastMoving_right)[], Vector2f fastBee_velocity){

	static bool stoppedBee[50] = {false};  //knowing which bee is stopped
	static float  Timer[50] = {0.f};  //Keep track of the time of stoppage
	static Clock stop;
	float elapsed_time = stop.restart().asSeconds();
	static bool stopped = false;   //it will make sure only one bee stops


      for(int i=0; i<index; i++){
        if(spawned[i]){

			if(!stoppedBee[i]){
				if (moving_right[i]) {
					// Move right if moving_right[i] is true
					if ((bee[i].getPosition().x < window.getSize().x - static_cast<int>(bee[i].getTextureRect().width))) {
						bee[i].move(bee_velocity);
					}
					else {
						//Changing direction of motion
						moving_right[i] = false; 
					}
				} 
				else {
					// Move left if moving_right[i] is false
					if (bee[i].getPosition().x > 0) {
						bee[i].move(-bee_velocity);
					} 
					else {
						//Changing direction of motion
						moving_right[i] = true;  
					}
				}

			}
			else{

				
				
				Timer[i] += elapsed_time;
				if(Timer[i] > 5.f){

					Timer[i] = 0.f;
					stoppedBee[i] = false;
					stopped = false;
				}
				
			
			}

			//Selecting a random bee to stop for 5 seconds
			
			if(!stopped){
				//Stopping randomm bee for some time
				int random_index = rand() % 20;
				if(!stoppedBee[random_index] && spawned[i]){
					stoppedBee[random_index] = {true};
					Timer[random_index] = 0.f;
					stopped = true;
				}


			}
			
				

			
			

			

	    } 
      
      
    }


	//Donot know why the level >1 not working properly resulting in unexpected behaviors and level!=1 working great
	//if(level > 1){

		for(int i=0; i<fastbeeIndex; i++){

			if(fastSpawned[i]){

				if(fastMoving_right[i]){

					if ((fast_bee[i].getPosition().x < window.getSize().x - static_cast<int>(fast_bee[i].getTextureRect().width))) {
						fast_bee[i].move(fastBee_velocity);
					}
					else {
						fastMoving_right[i] = false;  // Change direction to left when reaching the right edge
					}
				}
				else{

					if (fast_bee[i].getPosition().x > 0) {
						fast_bee[i].move(-fastBee_velocity);
					} 
					else {
						fastMoving_right[i] = true;  // Change direction to right when reaching the left edge
					}
				}
			}
		}
	//}	


}

void bee_direction(sf::Sprite (&bee)[], int index, bool (&spawned)[], sf::RenderWindow& window, Sprite (&fast_bee)[], bool (&fastSpawned)[], int fastbeeIndex, int &level){
               
                for(int i=0; i<index; i++){
                      if(spawned[i]){
                            if(bee[i].getPosition().x + bee[i].getTextureRect().width >= window.getSize().x  &&
                               bee[i].getPosition().y + bee[i].getTextureRect().height < window.getSize().y - 128){
                                //&& bee[i].getPosition().y + bee[i].getGlobalBounds().height <window.getSize().y
                                bee[i].move(0.f, 10.f);
                            }
							else if(bee[i].getPosition().x <= 0  &&
                               bee[i].getPosition().y + bee[i].getTextureRect().height < window.getSize().y - 150){

								bee[i].move(0.f, 10.f);
							   }
                          
                      }
                      
                    
                }

				//Chaning the direction of fast bees
				if(level != 1){

					for(int i=0; i<fastbeeIndex; i++){

						if(fastSpawned[i]){

							if(fast_bee[i].getPosition().x + fast_bee[i].getTextureRect().width >= window.getSize().x  &&
                               fast_bee[i].getPosition().y + fast_bee[i].getTextureRect().height < window.getSize().y - 100){
                                //&& bee[i].getPosition().y + bee[i].getGlobalBounds().height <window.getSize().y
                                fast_bee[i].move(0.f, 10.f);
                            }
							else if(fast_bee[i].getPosition().x <= 0  &&
                               fast_bee[i].getPosition().y + bee[i].getTextureRect().height < window.getSize().y - 100){

								fast_bee[i].move(0.f, 10.f);
							   }
                          							
						}
					}
				}
}

void bee_Collision_bullet(sf::Sprite (&bee)[], bool (&spawned)[], int index, bool &bullet_exist, sf::Sprite bullet, bool (&comb)[], sf::Sprite (&honey_comb)[], Music &strikeSound, Music &bgMusic, bool (&fastSpawn)[], Sprite (&fast_bee)[], int fastbeeIndex, bool (&redcomb_spawn)[], int &bee_strike, int &level, int &leftbullets, int &points){

				//Checking for collision of bullet with normal bees
              	for(int i=0; i<index; i++){
                      if(spawned[i]){

							float bee_x = bee[i].getPosition().x;
							float bee_y = bee[i].getPosition().y;

							float bullet_x = bullet.getPosition().x;
							float bullet_y = bullet.getPosition().y;

                            //Checking Collision of bullet and bees

							if(bullet_exist && (bullet_x + bullet.getTextureRect().width >= bee_x && bullet_x  <= bee_x + bee[i].getTextureRect().width)  
								&& (bullet_y >= bee_y && bullet_y <= bee_y + bee[i].getTextureRect().height) ){
									spawned[i] = false;
									bullet_exist = false;
									leftbullets -= 1;
									comb[i] = true;
									bee_strike+=1;
									points+=100;

									//Playing the sound
									strikeSound.play();
									bgMusic.setVolume(0);
									break;
							}

                            
                      }
					  
              }

			  //Checking for collision of bullet with fast bees
			  if(level>1){

				for(int i=0; i<fastbeeIndex; i++){
					
					if(fastSpawn[i]){
						
						//getting its x and y coordinate
						float fast_x = fast_bee[i].getPosition().x;
						float fast_y = fast_bee[i].getPosition().y;

						
						float bullet_x = bullet.getPosition().x;
						float bullet_y = bullet.getPosition().y;

						//Checking for collision
						if(bullet_exist && (bullet_x + bullet.getTextureRect().width >= fast_x &&
						   bullet_x <= fast_x + fast_bee[i].getTextureRect().width &&
						   bullet_y >= fast_y && 
						   bullet_y <= fast_y + fast_bee[i].getTextureRect().height)){

									fastSpawn[i] = false;
									leftbullets -= 1;
									redcomb_spawn[i] = true;
									bullet_exist = false;
									points += 1000;

									//Playing the sound
									strikeSound.play();
									bgMusic.setVolume(0);
									break;

						   }
					}
				}
			  }

			

		
}

void red_honey_combs(Sprite (&red_combs)[], bool (&spawned_redComn)[], Sprite (&fast_bee)[], int &fastbeeIndex, Texture &redComb_texture, Vector2f &comb_scale){

			for(int i=0; i<fastbeeIndex; i++){
                      if(spawned_redComn[i]){
                          float bee_x = fast_bee[i].getPosition().x;
                          float bee_y = fast_bee[i].getPosition().y;
                          red_combs[i].setTexture(redComb_texture);
                          red_combs[i].setPosition(bee_x, bee_y);
						  red_combs[i].setScale(comb_scale);
                      }
              }


}
void pre_gen_honey_comb(Sprite (&honey_combs)[], Texture &texture, RenderWindow &window,  bool (&pregen_comb)[], int &pre_gen, Vector2f &comb_scale){
	for(int i=0; i<pre_gen; i++){

		if(pregen_comb[i]){

			if (!honey_combs[i].getTexture()) { 
                honey_combs[i].setTexture(texture);
				honey_combs[i].setScale(comb_scale);
                honey_combs[i].setPosition(
                    static_cast<float>(rand() % (window.getSize().x - static_cast<int>(honey_combs[i].getTextureRect().width))),
                    static_cast<float>(rand() % 300)
                );
			}

		}
		
	}
}
void honey_combs(sf::Sprite (&honey_comb)[], bool (&comb)[], sf::Texture &texture, sf::Sprite (&bee)[], int index, Vector2f &comb_scale){

              for(int i=0; i<index; i++){
                      if(comb[i]){
                          float bee_x = bee[i].getPosition().x;
                          float bee_y = bee[i].getPosition().y;
                          honey_comb[i].setTexture(texture);
                          honey_comb[i].setPosition(bee_x, bee_y);
						  honey_comb[i].setScale(comb_scale);
                      }
              }

}




void honey_combs_collision(sf::Sprite(&honey_comb)[], bool (&comb)[], int bee_index, sf::Sprite bullet, bool &bullet_exist, Music &obstacleSound, Sprite (&pregen_comb)[], bool (&spawned_pregen)[], Sprite (&red_combs)[], bool (&spawned_redComb)[], int fastbeeIndex, bool (&hit)[], int &level, int &pre_gen, int &leftbullets){
            //Checking Collision of bullet and honeycombs
			float bullet_x = bullet.getPosition().x;
			float bullet_y = bullet.getPosition().y;
            for(int i=0; i<bee_index; i++){

							

							float honey_comb_x = honey_comb[i].getPosition().x;
							float honey_comb_y = honey_comb[i].getPosition().y;

							if(bullet_exist && comb[i] && (bullet_x + bullet.getTextureRect().width>=honey_comb_x && bullet_x <=honey_comb_x+honey_comb[i].getTextureRect().width)
								&& (bullet_y>=honey_comb_y && bullet_y<=honey_comb_y+honey_comb[i].getTextureRect().height)){
									comb[i] = false;
                                    bullet_exist = false;
									leftbullets -= 1;

									//Playing the sound
									obstacleSound.play();
								
							}
							// else if(bullet_exist && spawned_pregen[i] && (bullet_x + bullet.getTextureRect().width>=pregen_comb[i].getPosition().x && bullet_x <=pregen_comb[i].getPosition().x+pregen_comb[i].getTextureRect().width)
							// 	&& (bullet_y>=pregen_comb[i].getPosition().y && bullet_y<=pregen_comb[i].getPosition().y+pregen_comb[i].getTextureRect().height)){
							// 		spawned_pregen[i] = false;
                            //         bullet_exist = false;

							// 		//Playing the sound
							// 		obstacleSound.play();
								
							// }

                            
            }

			//Checking collision with pre generated combs
			for(int i=0; i<pre_gen; i++){

				if(bullet_exist && spawned_pregen[i] && (bullet_x + bullet.getTextureRect().width>=pregen_comb[i].getPosition().x && bullet_x <=pregen_comb[i].getPosition().x+pregen_comb[i].getTextureRect().width)
								&& (bullet_y>=pregen_comb[i].getPosition().y && bullet_y<=pregen_comb[i].getPosition().y+pregen_comb[i].getTextureRect().height)){
									spawned_pregen[i] = false;
                                    bullet_exist = false;
									leftbullets -= 1;

									//Playing the sound
									obstacleSound.play();
								
							}
			}

			//Checking collision with red combs
			for(int i=0; i<fastbeeIndex; i++){

				if(bullet_exist && spawned_redComb[i] &&
				   bullet_x + bullet.getTextureRect().width >= red_combs[i].getPosition().x &&
				   bullet_x <= red_combs[i].getPosition().x + red_combs[i].getTextureRect().width &&
				   bullet_y >= red_combs[i].getPosition().y &&
				   bullet_y <= red_combs[i].getPosition().y + red_combs[i].getTextureRect().height){

							//Removing the red comb and the bullet and playing sound
							spawned_redComb[i] = false;

							if(level == 4){
								hit[i] = true;
							}
							
							leftbullets -= 1;
							bullet_exist = false;
							obstacleSound.play();
				   }
			}
            

}


void startMenu(Text (&menu_text)[], RenderWindow &window, int &max_bees, Font &font, bool &start, Vector2f &bee_velocity, Texture &menuTexture, bool (&pregen_comb)[], Music &bgMusic, bool &levelUp, bool &fromMenu, bool (&hiveSpawned)[], Sprite (&bee_hive)[], int &level, int &pre_gen, int &max_fastbee, int &bee_amount, Text (&board)[], bool &pointboard){
		
		
		bgMusic.openFromFile("Music/Forest.ogg");
		if(!bgMusic.openFromFile("Music/Forest.ogg")){
			cout<<"Error opening the Music"<<endl;
			exit(0);
		}
		if (bgMusic.getStatus() != Music::Playing) {
			bgMusic.play();
			bgMusic.setVolume(50);
		}


		//Determing the number of bee
		if(level==1 || level==3){
			bee_amount = 20;
		}
		else if(level==2){
			bee_amount = 15;
		}
		else if(level == 4){
			bee_amount = 20;
		}

		//Selecting fast bees based upon level
		if(level == 2){
			max_fastbee = 5;
		}
		else if(level == 3){
			max_fastbee = 10;
		}
		else if(level == 4){
			max_fastbee = 15;
		}
		else
			max_fastbee = 0;
		//For the first 5 second displaying the Background
		float elapsed_time = 0.f;
		Clock clock;
		
		//Sprite to display the background
		Sprite background;
		background.setTexture(menuTexture);
		//background.setScale(float (window.getSize().x/menuTexture.getSize().x), float(window.getSize().y/menuTexture.getSize().y));
		background.setPosition(float(resolutionX/2 - background.getTextureRect().width/2), float(resolutionY/2 - background.getTextureRect().height/2));
	    while(true){
					//Setting the text of the menu
					menu_text[0].setString("Start Level 1 (Enter)\n \nBOSS Level (Up)\n \nScore Board (Down)\n \nExit (ESC)");
					menu_text[1].setString("Start Level 2 (Enter)\n \nBOSS Level (Up)\n \nScore Board (Down)\n \nExit (ESC)");
					menu_text[2].setString("Start Level 3 (Enter)\n \nBOSS Level (Up)\n \nScore Board (Down)\n \nExit (ESC)");
					menu_text[3].setString("BOSS Level (Enter)\nExit (ESC)");



					//Setting the Font and color of the menu
					for (int i = 0; i < 4; i++) {
						menu_text[i].setFont(font);
						menu_text[i].setCharacterSize(50);
						menu_text[i].setFillColor(Color::Green);

						//Positioning the text in the center
						FloatRect position(menu_text[i].getGlobalBounds());
						
						menu_text[i].setPosition(resolutionX/2 - position.width/2, 100);

					}
					
					//Setting the Position of the Menu text
					// menu_text[0].setPosition(resolutionX/2, 200);
					// menu_text[1].setPosition(resolutionX/2, 300);
					// menu_text[2].setPosition(resolutionX/2, 400);

					elapsed_time += clock.restart().asSeconds();

					window.clear();

					if(elapsed_time < 3.f)
						window.draw(background);
					else{
						switch (level)
						{
							case 1: window.draw(menu_text[0]);
									break;
							case 2: window.draw(menu_text[1]);
									break;
							case 3: window.draw(menu_text[2]);
									break;
							case 4: window.draw(menu_text[3]);
						}
					}
					
					window.display();

					Event selection;
					while(window.pollEvent(selection)){
						if(selection.type == Event::KeyPressed){
								if(selection.key.code == Keyboard::Enter){
									switch(level){
										case 1: max_bees = bee_amount;
												pre_gen = 3;
												break;
										case 2: max_bees = bee_amount;
												pre_gen = 9;
												break;
										case 3: max_bees = bee_amount;
												pre_gen = 15;
												break;
										case 4: max_bees = bee_amount;
												pre_gen = 15;

									}

									//Pregenerated honeyCombs
									for(int i=0; i<pre_gen; i++){
										pregen_comb[i] = true;
									}
									start = false;
									break;
								}
								else if(selection.key.code == Keyboard::Up){

									level = 4;
									max_bees = 20;
									max_fastbee = 15;
									pre_gen = 15;
									levelUp = true;
									fromMenu = true;
									
								}
								else if(selection.key.code == Keyboard::Down){
									
									//pointboard = true;
								
									scoreBoard(board, window);
									continue;
								}
								else if(selection.key.code == Keyboard::Escape){
									exit(0);
								}
								else{
									fromMenu = false;
									continue;
								}
									
							}
						else if(selection.type == Event::Closed){
								exit(0);
						}

						

							


						}	
						if(!start)
							break;
	}

	//Spawning bee hive if the level is 4
	if(level == 4){
		pregenHives(hiveSpawned, bee_hive);
	}

}

void collision_player(Sprite &player, Sprite (&fast_bee)[], int maxfastBees, bool &gameover){

		
		for(int i=0; i<maxfastBees; i++){

			//if(bee[i]){

				//Getting position of the player and bee;
				float player_x = player.getPosition().x;
				float player_y = player.getPosition().y;

				float bee_x = fast_bee[i].getPosition().x;
				float bee_y = fast_bee[i].getPosition().y;

				//Checking for collision
				if((player_x + player.getTextureRect().width>=bee_x && player_x <=bee_x+fast_bee[i].getTextureRect().width)
				   && (player_y>=bee_y && player_y<=bee_y+fast_bee[i].getTextureRect().height)){
							gameover = true;
				   }

			//}
		}

}


void gameOverMenu(Sprite &gameovertext, RenderWindow &Window, bool &gameover, bool &start, int &level){
	float elapsedTime = 0.f;
	Clock clock;

	while(elapsedTime <= 5.f){

		elapsedTime += clock.restart().asSeconds();
		Window.clear();
		Window.draw(gameovertext);
		Window.display();

	}
	gameover = false;
	start = true;
	level = 1;
}



void bee_collision_combs(Sprite (&combs)[], Sprite (&pregen_comb)[], Sprite (&bee)[], bool (&spawnBee)[], bool (&spawnComb)[], bool (&spawnPregen)[], int max_combs, bool (&moving_right)[], Sprite (&fast_bee)[], Sprite (&red_comb)[], bool (&spawned_redComb)[], bool (&spawned_fastBee)[], bool (&fastMoving_right)[], int &fastbeeIndex) {
    //collision = false; // Initialize as false at the start of the function

    for (int i=0; i < max_combs; i++) {
			if (spawnBee[i]) {
				//Checking collision with al the combs
				for (int j=0; j < max_combs; j++){

					if (spawnComb[j] && bee[i].getGlobalBounds().intersects(combs[j].getGlobalBounds())){
						
						//Moving the bee downward by 10 pixels
						bee[i].move(0.f, 10.f);

						//Changing the direction of its motion
						if(moving_right[i])
							moving_right[i] = false;
						else
							moving_right[i] = true;
					}

					if (spawnPregen[j] && bee[i].getGlobalBounds().intersects(pregen_comb[j].getGlobalBounds())){

						//Moving down
						bee[i].move(0.f, 10.f);
						//Changing direction
						if(moving_right[i])
							moving_right[i] = false;
						else
							moving_right[i] = true;

					}
			}
		}


	}

	//Checking collision of red combs with red
	for(int i=0; i<fastbeeIndex; i++){

			if(spawned_fastBee[i]){

				for(int j=0; j<fastbeeIndex; j++){

					if(spawned_redComb[j] && fast_bee[i].getGlobalBounds().intersects(red_comb[j].getGlobalBounds())){

						fast_bee[i].move(0.f, 10.f);

						//Chanigin its direction of motion
						if(fastMoving_right[i])
							fastMoving_right[i] = false;
						else
							fastMoving_right[i] = true;

					}
				}
			}
	}
}


void polination(Sprite (&bee)[], bool (&already_spawned)[], int bee_index, RenderWindow &window, Texture flowerTexture, Sprite (&flowers)[], bool (&liveFlower)[], int &flowercount, const int &max_flowers){

	
	
	for(int i=0; i<bee_index; i++){


		if(already_spawned[i]){

			Vector2f bee_coordinates(bee[i].getPosition().x, bee[i].getPosition().y);
			Vector2f window_coordinates(window.getSize().x, window.getSize().y);

			if(bee_coordinates.x + bee[i].getTextureRect().width >= window_coordinates.x &&
			   bee_coordinates.y + bee[i].getTextureRect().height >= window_coordinates.y - 150){

						// removing the bee at the edge
						already_spawned[i] = false;

						//Putting flowers on the edges
						if (flowercount < max_flowers) {

							if (flowercount == 0){ 
								//flowers[flowercount].setTexture(flowerTexture);
								flowers[flowercount].setScale(2.f, 2.f);
								flowers[flowercount].setPosition(0.f, window_coordinates.y - 120.f);
								liveFlower[flowercount] = true;
								flowercount++;

								//flowers[flowercount].setTexture(flowerTexture);
								flowers[flowercount].setScale(2.f, 2.f);
								flowers[flowercount].setPosition(window_coordinates.x - flowers[flowercount].getTextureRect().width - 35, window_coordinates.y - 120.f);
								liveFlower[flowercount] = true;
								flowercount++;
							}
							else{
								
								//flowers[flowercount].setTexture(flowerTexture);
								flowers[flowercount].setScale(2.f, 2.f);
								flowers[flowercount].setPosition(window_coordinates.x - flowers[flowercount].getTextureRect().width*flowercount - 17.f * flowercount , window_coordinates.y - 120.f);
								liveFlower[flowercount] = true;
								//cout<<"FlowerCount:"<<flowercount<<endl;
								flowercount++;

							}
			   }
		}
	}

}

}

void lives(Sprite (&live)[], bool (&spawnedLive)[], Texture &liveTexture, RenderWindow &window, int &counter, bool &gameover, int &max_lives, int &leftbullets, const int &maxBulletperLevel){


		for(int i=0; i<max_lives; i++){

			if(!live[i].getTexture()){

				live[i].setTexture(liveTexture);
				live[i].setColor(Color::Black);
				live[i].setPosition(window.getSize().x - live[i].getTextureRect().width*(i+1), window.getSize().y - live[i].getTextureRect().height);
				spawnedLive[i] = true;
			}

		}

		if(leftbullets == 0){

			leftbullets = maxBulletperLevel;

			for(int i=max_lives - 1; i>=0; i--){

				if(spawnedLive[i]){

					spawnedLive[i] = false;
					counter ++;
					break;
				}
			}
		}

		if(counter > max_lives)
			gameover = true;

		
		

}


void hummingBird(Sprite &bird, RenderWindow &window, Sprite (&honey_comb)[], bool (&spawned_comb)[], bool &bird_exist, float &respawnTime, Sprite (&pregen_combs)[], bool (&spawnedPregen)[], int (&honeyComb_tier)[], int (&pregenComb_tier)[], Sprite (&red_combs)[], bool (&spawned_redComb)[], int (&redComb_tier)[], bool (&hit)[], int &points, int &level, int &max_fastbee, int &bee_amount, int &pre_gen, const int &maximumfastbees) {
    static Clock birdMoveClock;
	static Clock birdRespawn;
	
    static float elapsedTime = 0.f;
    static Vector2f targetPosition;
    static bool start = false;
	static bool atTarget = false;

	if(bird_exist){

			if (!start)
			{
				

				//Setting a random destination for the bird
				targetPosition.x = rand() % (window.getSize().x - 50) + 50;
				targetPosition.y = rand() % (window.getSize().y - 140) + 50;
				start = true;
			}

			elapsedTime += birdMoveClock.restart().asSeconds();

			if (elapsedTime < 5.f)
			{
				//Moving the bird towards that position
				Vector2f moveSpeed = targetPosition - bird.getPosition();
				if(bird.getPosition() != targetPosition){

					moveSpeed = moveSpeed / 100.f;  //Adjusting the speed of the bird
					bird.move(moveSpeed);
				}
					
			}
			else
			{
				//Resetting the timer and the target position after every 5 seconds
				elapsedTime = 0.f;
				atTarget = true;
				targetPosition.x = rand() % (window.getSize().x - 50) + 50;
				targetPosition.y = rand() % (window.getSize().y - 140) + 50;
			}

			


			//Checking if the target position collides with the honey comb
			for(int i=0; i<bee_amount; i++){
				
				if(spawned_comb[i]){

						if(atTarget){

							
								if(bird.getGlobalBounds().intersects(honey_comb[i].getGlobalBounds())){

									spawned_comb[i] = false;

									//Increamenting the point based on the tier
									if(honeyComb_tier[i] == 1 || honeyComb_tier[i] == 2)
										points+= 1000;
									else if(honeyComb_tier[i] == 3 || honeyComb_tier[i] == 4 || honeyComb_tier[i] == 5)
										points += 800;
									else	
										points += 500;

									//Setting the flag to false
									atTarget = false;
								}
						}
				}
			}

			for(int i=0; i<pre_gen; i++){

				if(spawnedPregen[i]){

					
					if(atTarget){

						if(bird.getGlobalBounds().intersects(pregen_combs[i].getGlobalBounds())){

							spawnedPregen[i] = false;
							//Increamenting the point based on the tier
							if(pregenComb_tier[i] == 1 || pregenComb_tier[i] == 2)
								points+= 1000;
							else if(pregenComb_tier[i] == 3 || pregenComb_tier[i] == 4 || pregenComb_tier[i] == 5)
								points += 800;
							else	
								points += 500;

							//Setting the flag to false
							atTarget = false;
						}
					}
				}
			}

			if(level > 1){

				for(int i=0; i<maximumfastbees; i++){

					if(spawned_redComb[i]){

						if(atTarget){

							if(bird.getGlobalBounds().intersects(red_combs[i].getGlobalBounds())){
								
								//If it is the boss level then applying powers
								if(level == 4){
									hit[i] = true;
								}
								spawned_redComb[i] = false;
								//Increamenting the point based on the tier
								if(redComb_tier[i] == 1 || redComb_tier[i] == 2)
									points+= 2000;
								else if(redComb_tier[i] == 3 || redComb_tier[i] == 4 || redComb_tier[i] == 5)
									points += 1800;
								else	
									points += 1500;

								//Setting the flag to false
								atTarget = false;
							}
						}
					}
				}

			}



	}
	else{

		
		//Counting to 5 before respawning the bird
		respawnTime += birdRespawn.restart().asSeconds();

		cout<<"Respawn Time: "<<respawnTime<<endl;

		if(respawnTime >= 5.f){
			cout<<"The bird is set true again: "<<endl;
			
			bird_exist = true;
			respawnTime = 0.f;
			start = false;

			birdRespawn.restart();
		}
		
	}
    
}

void collision_bird(Sprite (&bird), Sprite &bulletSprite, bool &bullet_exist, bool &bird_exist, int &birdStrike, int &leftbullets){


		if(bullet_exist && bird_exist){

			//Getting there position
			Vector2f bullet_coordinates(bulletSprite.getPosition());
			Vector2f bird_coordinates(bird.getPosition());
			
			//Checking for collision
			if((bullet_coordinates.x + bulletSprite.getTextureRect().width >= bird_coordinates.x &&
			   bullet_coordinates.x <= bird_coordinates.x + bird.getTextureRect().width) &&
			   (bullet_coordinates.y >= bird_coordinates.y &&
			    bullet_coordinates.y <= bird_coordinates.y + bird.getTextureRect().height)){


								bullet_exist = false;
								leftbullets -= 1;
								birdStrike++;

								cout<<"Bird Strike "<<birdStrike<<endl;

								if(birdStrike >= 3){
									bird_exist = false;
									cout<<"Bird exist has been set to false"<<endl;
									birdStrike = 0;
								}
				}
		}
}


void beeHive(Sprite (&bee)[], Sprite (&honey_comb)[], bool (already_spawned)[], bool (&comb)[], RenderWindow &window, Sprite (&bee_hive)[], bool (&hiveSpawned)[], int &bee_amount, const int &max_combs) {

	//Spawning a bee hive where the bee get stuck
    for (int i = 0; i < bee_amount; i++){
        if(already_spawned[i]){
            //Getting coordinates of the bee
            Vector2f bee_coordinates = bee[i].getPosition();
            FloatRect beeBounds = bee[i].getGlobalBounds();

            bool stuckBetweenCombs = false; //To track the status of the bee

            for(int j = 0; j < max_combs; j++){
                if(comb[j]){
                    // Getting honeycombs coordinates and bounds
                    FloatRect combBounds = honey_comb[j].getGlobalBounds();


                    // Checking if the bee is stuck between two combs
                    for(int k = 0; k < max_combs; k++){
						
						//IF the two combs are not the same combs then checking stuck
                        if (j != k && comb[k]) {
                            FloatRect otherCombBounds = honey_comb[k].getGlobalBounds();
                            if (combBounds.intersects(beeBounds) && otherCombBounds.intersects(beeBounds)) {
                                stuckBetweenCombs = true;
                                break;
                            }
                        }
                    }

                    // Check if the bee is stuck between a comb and the screen edges
                    bool stuckAtEdge = (beeBounds.left <= 0 || 
                                       beeBounds.left + beeBounds.width >= window.getSize().x) && 
                                       combBounds.intersects(beeBounds);

                    if (stuckBetweenCombs || stuckAtEdge) {
                        already_spawned[i] = false;
						// if(!hiveSpawned[i]){

						// 	hiveSpawned[i] = true;
						// 	bee_hive[i].setPosition(bee[i].getPosition().x, bee[i].getPosition().y);

						// }
						hiveSpawned[i] = true;
						bee_hive[i].setPosition(bee[i].getPosition().x, bee[i].getPosition().y);

                        break;
                    }
                }
            }
        }
    }
}

void levelUp(bool &levelUp, bool (&already_spawned)[], bool start, int &bee_amount, bool (&fastSpawned)[], int &max_fastbee){

	if(!start){

		for(int i=0; i<bee_amount; i++){

			if(already_spawned[i]){

				levelUp = false;
				return;
			}	
			else
				levelUp = true;
		}

		for(int i=0; i<max_fastbee; i++){
			if(fastSpawned[i]){
				levelUp = false;
				return;
			}
			else
				levelUp = true;
		}
		
	}
}

void tiers(Sprite (&pregen_comb)[], bool (&pregenSpawned)[], int (&pregenComb_tier)[], Sprite (&honey_combs)[], bool (&spawnedComb)[], int bee_index, int (&honeyComb_tier)[], Sprite (&red_comb)[], bool (&spawnedRed_comb)[], int (&redComb_tier)[], Sprite (&beeHive)[], bool (&spawnedbee_hive)[], int (&beeHive_tier)[], int &pre_gen, int &level, const int &maximumfastbees){


	//Determining the tier of the pre generated combs
	for(int i=0; i<pre_gen; i++){

		if(pregenSpawned[i]){

			//Getting its positions
			Vector2f coordinates(pregen_comb[i].getPosition());

			if(coordinates.y > 0.f && coordinates.y <= 32.f)
				pregenComb_tier[i] = 1;
			else if(coordinates.y > 32.f && coordinates.y <= 64.f)
				pregenComb_tier[i] = 2;
			else if(coordinates.y > 64.f && coordinates.y <= 96.f)
				pregenComb_tier[i] = 3;
			else if(coordinates.y > 96.f && coordinates.y <= 129.f)
				pregenComb_tier[i] = 4;
			else if(coordinates.y > 129.f && coordinates.y <= 161.f)
				pregenComb_tier[i] = 5;
			else
				pregenComb_tier[i] = 6;
		}
	}

	//Determining the tiers of the honeycombs

	for(int i=0; i<bee_index; i++){

		if(spawnedComb[i]){

			//Getting positions
			Vector2f coordinates(honey_combs[i].getPosition());

			if(coordinates.y > 0.f && coordinates.y <= 32.f)
				honeyComb_tier[i] = 1;
			else if(coordinates.y > 32.f && coordinates.y <= 64.f)
				honeyComb_tier[i] = 2;
			else if(coordinates.y > 64.f && coordinates.y <= 96.f)
				honeyComb_tier[i] = 3;
			else if(coordinates.y > 96.f && coordinates.y <= 129.f)
				honeyComb_tier[i] = 4;
			else if(coordinates.y > 129.f && coordinates.y <= 161.f)
				honeyComb_tier[i] = 5;
			else
				honeyComb_tier[i] = 6;

		}
	}

	//Determining the tiers of the red Honeycombs
	if(level > 1){


		for(int i=0; i<maximumfastbees; i++){


			if(spawnedRed_comb[i]){

				Vector2f coordinates(red_comb[i].getPosition());

				if(coordinates.y > 0.f && coordinates.y <= 32.f)
					redComb_tier[i] = 1;
				else if(coordinates.y > 32.f && coordinates.y <= 64.f)
					redComb_tier[i] = 2;
				else if(coordinates.y > 64.f && coordinates.y <= 96.f)
					redComb_tier[i] = 3;
				else if(coordinates.y > 96.f && coordinates.y <= 129.f)
					redComb_tier[i] = 4;
				else if(coordinates.y > 129.f && coordinates.y <= 161.f)
					redComb_tier[i] = 5;
				else
					redComb_tier[i] = 6;
			}
		}
	}

	//Determiining the tiers of the bee hives

	for(int i=0; i<bee_index; i++){

		if(spawnedbee_hive[i]){

			//Determing the position of the bee hive
			Vector2f coordinates(beeHive[i].getPosition());

			if(coordinates.y > 0.f && coordinates.y <= 32.f)
				beeHive_tier[i] = 1;
			else if(coordinates.y > 32.f && coordinates.y <= 64.f)
				beeHive_tier[i] = 2;
			else if(coordinates.y > 64.f && coordinates.y <= 96.f)
				beeHive_tier[i] = 3;
			else if(coordinates.y > 96.f && coordinates.y <= 129.f)
				beeHive_tier[i] = 4;
			else if(coordinates.y > 129.f && coordinates.y <= 161.f)
				beeHive_tier[i] = 5;
			else
				beeHive_tier[i] = 6;
		}
	}
}

void beeHive_points(Sprite (&bee_hive)[], bool (&SpawnedHive)[], int (&beeHive_tier)[], int &bee_amount, int &points){

	static bool tier_checked[50] = {false};
	//Tranversing through all the bee hives
	for(int i=0; i<bee_amount; i++){

		//Checking if the hive is active or not
		if(SpawnedHive[i]){


			//Increamenting points based on its tiers
			if(!tier_checked[i]){

				if(beeHive_tier[i] == 1 || beeHive_tier[i] == 2){
					tier_checked[i] = true;
					points += 2000;
					break;
				}
				else if(beeHive_tier[i] == 3 || beeHive_tier[i] == 4 || beeHive_tier[i] == 5){
					tier_checked[i] = true;
					points += 1600;
					break;
				}
				else {
					tier_checked[i] = true;
					points += 1000;
					break;
				}
			}
			
		}
	}
}

void bonusLives(Sprite (&lives)[], bool (&spawned_live)[], int &points, int &max_lives){

	bool bonus = false;			//Local flag to determine the validity for bonus
	static bool visited[3] = {false};

	//Giving a bonus live based on the points
	if(points >= 20000){
		if(!visited[0]){
			max_lives ++;
			bonus = true;
			visited[0] = true;
		}
		
	}

	if(points >= 40000){
		if(!visited[1]){
			max_lives ++;
			bonus = true;
			visited[1] = true;
		}
		
	}

	if(points >= 80000){
		if(!visited[2]){
			max_lives ++;
			bonus = true;
			visited[2] = true;
		}
		
	}
	else
		bonus = false;




	if(bonus){
		//max_lives += 1;
		// //Iterating through all the lives
		// for(int i=0; i<max_lives; i++){

		// 	if(!spawned_live[i]){
		// 		//IF the live is not existing then make it exist and break
		// 		spawned_live[i] = true;
		// 		break;
		// 	}	
		
		// }
		if(!spawned_live[max_lives - 1]){

			spawned_live[max_lives - 1] = true;
			bonus = false;
		}


	}
	
}


void pregenHives(bool (&hiveSpawned)[], Sprite (&bee_hive)[]) {
    for(int i = 0; i < 5; i++) {
        float posi_x = rand() % 700 + 10;
        float posi_y = rand() % 400 + 10;

        hiveSpawned[i] = true;
        bee_hive[i].setPosition(posi_x, posi_y);
    }
}

void powers(Sprite (&PowerSprite)[], Texture &speedInc, Texture &speedDec, Texture &heightInc, Texture &heightDec, RenderWindow &window, bool (&activePowerSprite)[], bool (&hit)[], Sprite (&red_comb)[], int (&power_index)[], bool(&grantPower)[], const int &maximumfastbees){

	//Getting window coordinates
	Vector2f window_coordinates(window.getSize());

	for(int i=0; i<maximumfastbees; i++){

		if(hit[i]){

			//Getting the combs coordinates
			Vector2f comb_coordinates(red_comb[i].getPosition());
			srand(static_cast<unsigned>(time(0)));
			int random_index = rand() % 4 + 0;
			if(!activePowerSprite[i]){

				switch (random_index)
				{
					case 0: PowerSprite[i].setTexture(speedInc);
							PowerSprite[i].setPosition(comb_coordinates.x, comb_coordinates.y);
							power_index[i] = 1;
							break;
					case 1: PowerSprite[i].setTexture(speedDec);
							PowerSprite[i].setPosition(comb_coordinates.x, comb_coordinates.y);
							power_index[i] = 2;
							break;
					case 2: PowerSprite[i].setTexture(heightInc);
							PowerSprite[i].setPosition(comb_coordinates.x, comb_coordinates.y);
							power_index[i] = 3;
							break;
					case 3: PowerSprite[i].setTexture(heightDec);
							PowerSprite[i].setPosition(comb_coordinates.x, comb_coordinates.y);
							power_index[i] = 4;
				}
				//Assigning power indexes
				//grantPower[random_index] = true;
				activePowerSprite[i] = true;
			}
			hit[i] = false;
			
		}
	}
	
}

void powerMove(Sprite (&powerSprite)[], bool (&activePowerSprite)[], RenderWindow &window, float &posi_x, float &posi_y, int index){

	//Getting window coordinates
	Vector2f window_coordinates(window.getSize());

	if(posi_y < window_coordinates.y - 110){

		posi_y += 2.f;
		powerSprite[index].setPosition(posi_x, posi_y);
	}
}

void PlayerNameinput(Text &name, Text &inputname, string &playername, RenderWindow &window){

	window.clear();
	bool playerTyping = true;
	while(playerTyping){

			Event input;
			while(window.pollEvent(input)){

				if(input.type == Event :: Closed){
					window.close();
				}
				else if(input.type == Event :: KeyPressed){
					if(input.key.code == Keyboard::Enter){
						playerTyping = false;
					}

				}
				else{

					if(input.type == Event :: TextEntered){

						if(input.text.unicode){
							playername += static_cast<char>(input.text.unicode);
							inputname.setString(playername);
						}

						
					}
				}
			}
			window.clear();
			window.draw(name);
			window.draw(inputname);
			window.display();
	

	}
	

		
}

void scoreBoard(Text (&board)[], RenderWindow &window){

	
	//Local variables to store the data retieved from the file
	int points[10];
	string names[10];
	//Setting the first row as header
	board[0].setString("Score Board\n");

	//Extracting data from the file
	fstream myfile;
	myfile.open("record.txt", ios::in);
	while(myfile.is_open()){

		for(int i=0; i<10; i++){

			myfile >> names[i] >> points[i];
		}

		myfile.close();
	}

	//Storing the data in the text and displaying

	for(int i=0; i<10; i++){

		board[i + 1].setString( to_string(i+1) + '.' + names[i] + "      " + to_string(points[i]));
	}

	board[11].setString("Menu (Enter)");

	Event selection;
	while(true){

			while(window.pollEvent(selection)){

				if(selection.type == Event :: KeyPressed){

					if(selection.key.code == Keyboard::Enter){

						return;
					}
					
				}
				else if(selection.type == Event::Closed){
					exit(0);
				}

				
			}

			window.clear();
			for(int i=0; i<12; i++){
				window.draw(board[i]);

			}
			window.display();


	}
	
}

