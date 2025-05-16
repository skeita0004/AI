#include "../Library/GameObject.h"
#include "Screen.h"
#include "global.h"

class Stage : public GameObject
{
public:
	Stage();
	~Stage();

	void Update() override;
	void Draw() override;
};