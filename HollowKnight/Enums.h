#pragma once

enum class ESceneType
{
	GAME_START,
	DIRTMOUTH,
	CROSSROAD,
	MANTISTOWN,
	OBTAIN,
	STORE,
	ARENA,
	DEFEAT,
	VICTORY,
	ENUM_END
};

enum class EObjectType
{
	PLAYER,
	MONSTER,
	PROJECTILE,
	ITEM,
	GEO,
	LINE,
	TILE,
	HITBOX,
	EFFECT,
	SKILL,
	UI, 
	WALL,
	FRONTBG,
	IMAGE,
	STOREBOARD,
	ENUM_END
};

enum class EObjectState
{
	NODEAD,
	DEAD,
	ENUM_END
};

enum class EPlayerState
{
	IDLE,
	MOVE,
	JUMP,
	DOUBLEJUMP,
	FALL,
	DASH,
	CLIMB,
	WALLJUMP,
	SLASH,
	SLASH_UP,
	SLASH_DOWN,
	SHOOT,
	DAMAGED,
	FOCUSSTART,
	FOCUS,
	FOCUSGET,
	FOCUSEND,
	STUN,
	DEAD,
	FIGHTREADY,
	ENUM_END
};

enum class EMonsterType
{
	CRAWL,
	DASH,
	FLY,
	ORANGEFLY,
	BOSS,
	ENUM_END
};

enum class EBossType
{
	MANTISLORD,
	ENUM_END
};

enum class EMonsterState
{
	IDLE,
	MOVE,
	FLY,
	APPEAR,
	DASH_BEFORE,
	SLASH_BEFORE,
	WALL_TOP,
	WALL_BOTTOM,
	ROTATE,
	SHOOT,
	SPAWN,
	JUMP,
	DASH,
	DASH_AFTER,
	SLASH,
	SLASH_AFTER,
	SHOOT_TOP,
	SHOOT_BOTTOM,
	SHOOT_AFTER,
	ATTACK,
	FOLLOW,
	TURN,
	DAMAGED,
	STUN,
	NOTVISIBLE,
	DEAD,
	NOTHING,

	// �縶�� ����
	STAND,
	SIT,
	LEAVE,

	ENUM_END
};

enum class EProjectileOwnerType
{
	PLAYER,
	MONSTER,
	ENUM_END
};

enum class EProjectileType
{
	GUIDED_PROJECTILE,
	SCREW_PROJECTILE,
	BALL,
	ROTATEBALL,
	ENUM_END
};

enum class ELineType
{
	GROUND,
	WALL,
	ZIP,
	OBSTACLE,
	FLAG,
	ENUM_END
};

enum class ETileType
{
	GROUND,
	WALL,
	OBSTACLE,
	TRIGGER,
	ENUM_END
};

enum class EDirection
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	LU,
	RU,
	LD,
	RD,
	ENUM_END
};

enum class ERenderID
{
	BACKGROUND,
	BACK_EFFECT,
	GAMEOBJECT,
	FRONTGROUND,
	EFFECT,
	DEBUG_UI,
	UI,
	FRONT_UI,
	FRONT_FRONT_UI,
	ENUM_END
};

enum class EChannelID
{
	MOVEMENT,
	SKILL,
	HIT,
	DAMAGE,
	MONSTER,
	MONSTERVOICE,
	MONSTERSKILL,
	MONSTEREFFECT,
	BOSS,
	BOSSVOICE,
	BOSSSKILL,
	BOSSEFFECT,
	GEO,
	NPC,
	BGM,
	BGMBACK,
	ENUM_END
};