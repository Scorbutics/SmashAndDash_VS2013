#ifndef DEF_AMISSILE
#define DEF_AMISSILE

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "..\Character.h"
#include "../../Inputs\Readers\IniReader.h"
#include "../../Graphic\Texture.h"
#include "../../Physic\Particle.h"

using namespace std;


class Skill
{
    public:
	Skill(IniReader* data, Character* parent);
	
	unsigned int getRange();
	int getKnockback();
	void setKnockback(int knockback);
    Texture* getIcon();
    void setIcon(Texture* icon);
    string getName();
    void setPosIcon(SDL_Rect posIcone);
    SDL_Rect getPosIcon();
    void setName(string name);
    string getDescription();
    void setDescription(string description);
	virtual void launch(SDL_Rect dest) = 0;
    bool cooldownOK();
    Texture* getSpriteRemainingCD();
    string getType();
    Particle* getParticle(unsigned int number);
    void setType(string type);
    virtual void refresh() = 0;
	virtual void display() = 0;
    bool isActive(int number);
    int getNumber();
    virtual ~Skill();

    int getContext();

    protected:
    std::vector<unique_ptr<Particle>> m_particles;
    Character* m_parent;
    SDL_Color m_color;
    SDL_Rect m_src, m_dst, m_anim;
    vector<float> m_x, m_y; //m_x m_y seront des coordonn�es pr�cises (sans se limiter aux entiers pour les pixels)
    vector<bool> m_actif;
    Texture m_cooldownText;
    int m_comptAnim, m_direction, m_context, m_id;
    int m_cooldown, m_lastTimeCD, m_timeCD, m_degats, m_knockback;
	unsigned int m_range;
    Texture m_icone;
    string m_description, m_name, m_type, m_style1, m_style2;
    SDL_Rect m_posIcone;
	unique_ptr<Statistics> m_statsBuffAlly, m_statsBuffEnemy;
	int m_statusAlterAlly, m_statusAlterEnemy;
	static const unsigned int m_fontSize;

    private:
    Skill(Skill const& skillACopier);// Emp�che la copie
};
typedef std::unique_ptr<Skill> Skill_ptr;


class Projectile : public Skill
{
    public:
    Projectile(IniReader* data, Character* parent);
    virtual void refresh();
    virtual ~Projectile();
	void setSpeed(float vitesse);
	float getSpeed();
	virtual void display();
	void collision();
	void launch(SDL_Rect dest);
private:
    unsigned int m_t;
	int m_slopeNoise, m_noise, m_nombre;
	float m_vitesse;
};


class AOE : public Skill
{
public:
	AOE(IniReader* data, Character* parent);
	virtual void refresh();
	virtual void launch(SDL_Rect dest);
	virtual ~AOE();
	virtual void display();
private:
	bool m_active;

};


/*
class Melee : public Skill
{
    public:
    Melee(int id, string skill, string icone, SDL_Rect *posIcone, int degats, int knockback, string description, string nom, string type, int cooldown, int context, Character* parent);
    virtual void refresh();
    virtual ~Melee();

};*/

#endif
