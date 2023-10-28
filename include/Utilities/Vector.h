// Cataclysm Engine's Vector Implementation

#ifndef NOKU_MUSIC_VECTOR_H
#define NOKU_MUSIC_VECTOR_H

#include <stdlib.h>
#include <math.h>


namespace NokuMusic {
    /**
     * @brief Struct that represents a 2D vector with X and Y components.
     * 
     */
    template<typename T>
    struct Vector2D {
        T X;   // The X component of the vector.
        T Y;   // The Y component of the vector.

        /**
         * @brief Returns an inverted version of the vector.
         * 
         * @return 
         */
        Vector2D Inverted() { return { -X, -Y }; }

        /**
         * @brief Inverts the components of the vector.
         * 
         */
        void Invert() { 
            X = -X;
            Y = -Y;
        }

        /**
         * @brief Returns a normalized version of the vector.
         * 
         * @return Vector2D 
         */
        Vector2D Normalized() {
            double vecMagnitude = GetMagnitude();
            return { X / vecMagnitude, Y / vecMagnitude };
        }

        /**
         * @brief Normalizes the vector.
         * 
         */
        void Normalize() {
            double vecMagnitude = GetMagnitude();
            X /= vecMagnitude;
            Y /= vecMagnitude;
        }

        /**
         * @brief Rounds the X component of the vector and returns it as an integer.
         * 
         * @return int
         */
        int IntX() { return round(X); }

        /**
         * @brief Rounds the Y component of the vector and returns it as an integer.
         * 
         * @return int 
         */
        int IntY() { return round(Y); }

        /**
         * @brief Returns a rounded version of the vector.
         * 
         * @return Vector2D 
         */
        Vector2D Rounded() { 
            return { round(X), round(Y) }; 
        }

        /**
         * @brief Rounds the components of the vector.
         * 
         */
        void Round() {
            X = round(X);
            Y = round(Y);
        }

        /**
         * @brief Returns the magnitude (length) of the vector.
         * 
         * @return double 
         */
        double GetMagnitude() {
            return sqrt((double)(X * X) + (double)(Y * Y));
        }

        static Vector2D Zero()   { return {  0,  0 }; }   // Represents a null vector.
        static Vector2D Up()     { return {  0,  1 }; }   // Represents a unit vector pointing straight up.
        static Vector2D Down()   { return {  0, -1 }; }   // Represents a unit vector pointing straight down.
        static Vector2D Left()   { return { -1,  0 }; }   // Represents a unit vector pointing straight to the left.
        static Vector2D Right()  { return {  1,  0 }; }   // Represents a unit vector pointing straight to the right.
        static Vector2D UpLeft() { return {  1, -1 }; }

        Vector2D& operator = (const Vector2D &second) {
            if (this != &second) {
                X = second.X;
                Y = second.Y;
            }
            return *this;
        }

        bool operator == (const Vector2D &second) const {
            return (X == second.X && Y == second.Y);
        }

        Vector2D operator + (const Vector2D &second) const {
            Vector2D result = *this;
            result += second;
            return result;
        }

        Vector2D& operator += (const Vector2D &second) {
            X += second.X;
            Y += second.Y;
            return *this;
        }

        Vector2D operator - (const Vector2D &second) const {
            Vector2D result = *this;
            result -= second;
            return *this;
        }

        Vector2D& operator -= (const Vector2D &second) {
            X -= second.X;
            Y -= second.Y;
            return *this;
        }

        Vector2D operator * (const Vector2D &second) const {
            Vector2D result = *this;
            result *= second;
            return result;
        }

        Vector2D operator * (const T &second) const {
            Vector2D result = *this;
            result *= second;
            return result;
        }

        Vector2D& operator *= (const Vector2D &second) {
            X *= second.X;
            Y *= second.Y;
            return *this;
        }

        Vector2D& operator *= (const T &second) {
            X *= second;
            Y *= second;
            return *this;
        }

        Vector2D operator / (const Vector2D &second) const {
            Vector2D result = *this;
            result /= second;
            return result;
        }

        Vector2D operator / (const T &second) const {
            Vector2D result = *this;
            result /= second;
            return result;
        }

        Vector2D& operator /= (const Vector2D &second) {
            X /= second.X;
            Y /= second.Y;
            return *this;
        }

        Vector2D& operator /= (const T &second) {
            X /= second;
            Y /= second;
            return *this;
        }
    };

    struct Vector3D {
        int X;
        int Y;
        int Z;
    };
}

#endif