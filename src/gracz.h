#pragma once
class Player
{
private:
	float player_x1;
	float player_x2;
	float player_y1;
	float player_y2;
	float player_z1;
	float player_z2;
	static Player* instance;
	Player();
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	static Player& getInstance();
	void RenderPlayer(float speed);
	void MovePlayer(float speed);
	float getPlayer_x1() const;
	float getPlayer_x2() const;
	float getPlayer_y1() const;
	float getPlayer_y2() const;
	float getPlayer_z1() const;
	float getPlayer_z2() const;
};

