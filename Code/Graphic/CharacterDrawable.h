#pragma once
#include "./Draw/Drawable.h"

class Character;

class CharacterDrawable : public Drawable
{
public:
	CharacterDrawable(Character* parent, int part);
	virtual void display() override;
	virtual int getPriority() const override;
	virtual ~CharacterDrawable();
private:
	Character* m_parent;
	int m_part;
};

