#include "character.h"
#include <QtMath>
#include <QColor>
#include <algorithm>

// ============================================================
// Character implementation
// Commit 2 (Apr 16)
// ============================================================

Character::Character(const QString &name, CharacterClass cls, bool isPlayer)
    : m_name(name), m_class(cls), m_isPlayer(isPlayer)
{
    m_stats = buildStats(cls);
    m_hp    = m_stats.maxHp;
    m_attackCooldownLeft = 0;
}

// ------- Stats factory ----------------------------------------
Stats Character::buildStats(CharacterClass cls) const
{
    switch (cls) {
    case CharacterClass::Warrior:
        return { /*maxHp*/150, /*atk*/25, /*def*/10, /*spd*/2.5f,
                 /*range*/50,  /*cooldown*/20 };
    case CharacterClass::Mage:
        return { 80,  35, 3, 3.0f, 200, 30 };
    case CharacterClass::Rogue:
        return { 100, 20, 5, 4.5f, 60,  15 };
    }
    return {};
}

// ------- Helpers -----------------------------------------------
float Character::hpPercent() const
{
    if (m_stats.maxHp == 0) return 0.f;
    return static_cast<float>(m_hp) / m_stats.maxHp;
}

QColor Character::color() const
{
    if (m_isPlayer) {
        switch (m_class) {
        case CharacterClass::Warrior: return QColor("#4A90D9");
        case CharacterClass::Mage:    return QColor("#9B59B6");
        case CharacterClass::Rogue:   return QColor("#27AE60");
        }
    }
    // Opponents are always reddish
    switch (m_class) {
    case CharacterClass::Warrior: return QColor("#E74C3C");
    case CharacterClass::Mage:    return QColor("#E67E22");
    case CharacterClass::Rogue:   return QColor("#C0392B");
    }
    return Qt::gray;
}

QString Character::classLabel() const
{
    switch (m_class) {
    case CharacterClass::Warrior: return "Warrior";
    case CharacterClass::Mage:    return "Mage";
    case CharacterClass::Rogue:   return "Rogue";
    }
    return "Unknown";
}

// ------- Movement & combat -------------------------------------
void Character::move(QPointF delta)
{
    m_pos += delta * m_stats.speed;
}

void Character::takeDamage(int rawDamage)
{
    int dmg = std::max(1, rawDamage - m_stats.defense);
    m_hp    = std::max(0, m_hp - dmg);
}

bool Character::tryAttack(Character &target)
{
    if (m_attackCooldownLeft > 0) return false;

    // Distance check
    QPointF diff  = target.position() - m_pos;
    float   dist  = static_cast<float>(qSqrt(diff.x()*diff.x() + diff.y()*diff.y()));
    if (dist > m_stats.attackRange) return false;

    target.takeDamage(m_stats.attack);
    m_attackCooldownLeft = m_stats.attackCooldown;
    return true;
}

void Character::tickCooldown()
{
    if (m_attackCooldownLeft > 0) --m_attackCooldownLeft;
}
