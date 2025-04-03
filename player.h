#pragma once

class Player
{
private:
	float xPos = -0.4f;
	float yPos = 0.0f;
	float velocity = 0.00013f;
	static Player* instance;
	unsigned int texture;
	Player();
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	static Player& getInstance();
	float GetXpos() const;
	float GetYpos() const;
	void SetYpos(float ypos);
	void MoveUp();
	void MoveDown();
	void Render();
	void Loss();
	void LoadBackground();
	void DrawBackground();
};

