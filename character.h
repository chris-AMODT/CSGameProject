#pragma once

#include <QString>
#include <QPointF>
#include <QColor>

// ============================================================
// Character — data model for every fighter on the battlefield
// Commit 2 (Apr 16): base class, no Qt widget deps yet
// ============================================================

enum class CharacterClass {
    Warrior,    // High HP, melee
    Mage,       // Low HP, ranged magic
    Rogue,      // Medium HP, fast, low defense
};

struct Stats {
    int maxHp;
    int attack;
    int defense;
    float speed;        // pixels per game tick
    int attackRange;    // pixels
    int attackCooldown; // ticks between attacks
};

class Character
{
public:
    Character() = default;
    Character(const QString &name, CharacterClass cls, bool isPlayer);

    // Accessors
    QString         name()        const { return m_name; }
    CharacterClass  charClass()   const { return m_class; }
    bool            isPlayer()    const { return m_isPlayer; }
    bool            isAlive()     const { return m_hp > 0; }
    int             hp()          const { return m_hp; }
    int             maxHp()       const { return m_stats.maxHp; }
    float           hpPercent()   const;
    QPointF         position()    const { return m_pos; }
    Stats           stats()       const { return m_stats; }
    int             attackCooldownLeft() const { return m_attackCooldownLeft; }

    // Mutators
    void setPosition(QPointF pos) { m_pos = pos; }
    void move(QPointF delta);
    void takeDamage(int rawDamage);
    bool tryAttack(Character &target);   // returns true if hit connected
    void tickCooldown();

    // Display helpers
    QColor color() const;
    QString classLabel() const;

private:
    Stats buildStats(CharacterClass cls) const;

    QString        m_name;
    CharacterClass m_class      = CharacterClass::Warrior;
    bool           m_isPlayer   = false;
    Stats          m_stats      = {};
    int            m_hp         = 0;
    QPointF        m_pos        = {0, 0};
    int            m_attackCooldownLeft = 0;
};
