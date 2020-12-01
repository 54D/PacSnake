#ifndef GHOST_H_
#define GHOST_H_

// TODO
// Include header

class Ghost {
public:
	// Need to discuss on the other type of ghost
	enum class GhostType {NORMAL, BIG};
	static double INIT_SPEED;
	
	Ghost();
	~Ghost();

private:
	GhostType type;
	double speed {INIT_SPEED};

	int health;
};


double Ghost::INIT_SPEED = 0.75;

#endif /* GHOST_H_ */