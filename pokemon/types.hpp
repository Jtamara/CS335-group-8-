#pragma once
#ifndef TYPES_H
#define TYPES_H

enum class Types {
    Fire,
    Grass,
    Water,
    Dark,
    Ghost,
    Normal,
    Ice,
    Ground,
    Fighting,
    Electric
};

static bool is_super_effective(const Types & attacking, const Types & defending) {
    switch(attacking) {
        case Types::Fire:
            if (defending == Types::Grass || defending == Types::Ice)
                return true;
            break;
        case Types::Grass:
            if (defending == Types::Water || defending == Types::Ground)
                return true;
            break;
        case Types::Water:
            if (defending == Types::Fire || defending == Types::Ground)
                return true;
            break;
        case Types::Dark:
            if (defending == Types::Ghost)
                return true;
            break;
        case Types::Ghost:
            if (defending == Types::Ghost)
                return true;
            break;
        case Types::Normal:
            if (defending == Types::Ghost)
                return true;
            break;
        case Types::Ice:
            if (defending == Types::Grass || defending == Types::Ground)
                return true;
            break;
        case Types::Ground:
            if (defending == Types::Fire || defending == Types::Electric)
                return true;
            break;
        case Types::Fighting:
            if (defending == Types::Normal || defending == Types::Ice)
                return true;
            break;
        case Types::Electric:
            if (defending == Types::Water)
                return true;
            break;
        default:
            return false;
    }
    return false;
};

static bool is_not_very_effective(const Types & attacking, const Types & defending) {
    switch(attacking) {
        case Types::Fire:
            if (defending == Types::Water || defending == Types::Ground)
                return true;
            break;
        case Types::Grass:
            if (defending == Types::Fire || defending == Types::Ice)
                return true;
            break;
        case Types::Water:
            if (defending == Types::Grass || defending == Types::Ice)
                return true;
            break;
        case Types::Dark:
            if (defending == Types::Fighting)
                return true;
            break;
        case Types::Ghost:
            if (defending == Types::Dark)
                return true;
            break;
        case Types::Normal:
            if (defending == Types::Fighting)
                return true;
            break;
        case Types::Ice:
            if (defending == Types::Fire || defending == Types::Water)
                return true;
            break;
        case Types::Ground:
            if (defending == Types::Grass || defending == Types::Ice)
                return true;
            break;
        case Types::Fighting:
            if (defending == Types::Ghost)
                return true;
            break;
        case Types::Electric:
            if (defending == Types::Ground)
                return true;
            break;
        default:
            return false;
    }
    return false;
};

#endif // TYPES_H