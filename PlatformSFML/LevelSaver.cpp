#include "LevelSaver.h"


int LevelSaver::saveLevel(std::fstream &out, Level &level)
{
	Character *ch = &level.characters[0];
	out << "hero " << ch->getOrigin().x << " " << ch->getOrigin().y << " " << ch->getPosition().x <<
		" " << ch->getPosition().y << " " << ch->getHP() << " " << ch->getMaxHP() << std::endl;

	for (int i = 1; i < level.characters.size(); i++) {
		ch = &level.characters[i];
		out << "npc " << ch->getOrigin().x << " " << ch->getOrigin().y << " " << ch->getPosition().x <<
			" " << ch->getPosition().y << " " << ch->getHP() << " " << ch->getMaxHP() << std::endl;
	}

	Weapon *w;
	for (int i = 0; i < level.weapons.size(); i++) {
		w = &level.weapons[i];
		if (w->invisible) continue;
		out << "weapon " << w->getOrigin().x << " " << w->getOrigin().y << " " << w->getPosition().x << " " << w->getPosition().y << " " << w->ammo << " " <<
			w->maxAmmo << " " << w->bulletVel.x << " " << w->bulletVel.y << " " << w->minDps << " " << w->maxDps << " " << w->cooldownTime << " " << w->shootFactor <<
			std::endl;
	}

	Block *b;
	for (int i = 0; i < level.blocks.size(); i++) {
		b = &level.blocks[i];
		out << "block " << b->getOrigin().x << " " << b->getOrigin().y << " " << b->getPosition().x << " " << b->getPosition().y << std::endl;
	}
	return 0;
}
