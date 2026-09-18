#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace ConsoleApp2::lsp
{

    namespace case1
    {
        namespace example
        {
            class Duck
            {
            public:
                virtual ~Duck() = default;
                virtual void Quack() const { std::cout << "Я крякаю\n"; }
                virtual void Fly() const { std::cout << "Я летаю\n"; }
            };
            class NyryayuschayaDuck : public Duck
            {
            public:
                void Quack() const override { std::cout << "КРЯЯЯЯЯ!!!!\n"; }
                void Fly() const override { std::cout << "Как-то летаю, всё ок\n"; }
                virtual void Dive() const { std::cout << "Look at my ass\n"; }
            };
            class CyborgDuck : public Duck
            {
            public:
                void Quack() const override { std::cout << "BEEP\n"; }
                void Fly() const override { throw std::runtime_error("Я НЕ УМЕЮ ЛЕТАТЬ!!!"); }
            };
        }

        namespace cooler_example
        {
            class IFlyable
            {
            public:
                virtual ~IFlyable() = default;
                virtual void Fly() const = 0;
            };
            class Duck
            {
            public:
                virtual ~Duck() = default;
                virtual void Quack() const { std::cout << "Я крякаю\n"; }
            };
            class NyryayuschayaDuck : public Duck, public IFlyable
            {
            public:
                void Quack() const override { std::cout << "КРЯЯЯЯЯ!!!!\n"; }
                void Fly() const override { std::cout << "Как-то летаю, всё ок\n"; }
                void Dive() const { std::cout << "Look at my ass\n"; }
            };
            class CyborgDuck : public Duck
            {
            public:
                void Quack() const override { std::cout << "BEEP\n"; }
                void DoLaser() const { std::cout << "вы умерли...\n"; }
            };
        }

        class Shape
        {
        public:
            virtual ~Shape() = default;
            virtual void SetWidth(int width)
            {
                Width = width;
                std::cout << "Width set to " << width << ".\n";
            }
            virtual void SetHeight(int height)
            {
                Height = height;
                std::cout << "Height set to " << height << ".\n";
            }
            virtual int CalculateArea() const { return Width * Height; }
            virtual void Draw() const { std::cout << "Drawing shape.\n"; }

        protected:
            int Width{}, Height{};
        };
        class Circle : public Shape
        {
        public:
            void SetWidth(int width) override
            {
                Width = Height = width;
                std::cout << "Circle diameter set to " << width << ".\n";
            }
            void SetHeight(int height) override
            {
                Width = Height = height;
                std::cout << "Circle diameter set to " << height << ".\n";
            }
            int CalculateArea() const override
            {
                return static_cast<int>(std::acos(-1.0) * (Width / 2) * (Width / 2));
            }
            void Draw() const override { std::cout << "Drawing circle.\n"; }
        };
    }

    namespace case2
    {
        class Vehicle
        {
        public:
            virtual ~Vehicle() = default;
            virtual void StartEngine() const { std::cout << "Engine started for vehicle " << LicensePlate << '\n'; }
            virtual void StopEngine() const { std::cout << "Engine stopped for vehicle " << LicensePlate << '\n'; }
            virtual void Refuel(double amount) { FuelLevel += amount; }
            virtual double GetFuelLevel() const { return FuelLevel; }
            virtual void Drive(double distance) { FuelLevel -= distance * 0.1; }
            std::string LicensePlate;
            double FuelLevel{}, FuelCapacity{};
        };
        class ElectricVehicle : public Vehicle
        {
        public:
            void Refuel(double) override { throw std::logic_error("Electric vehicles cannot be refueled with fuel"); }
            void StartEngine() const override { std::cout << "Electric vehicle " << LicensePlate << " started silently\n"; }
            void Drive(double distance) override { BatteryLevel -= distance * 0.2; }
            void Charge(double amount) { BatteryLevel += amount; }
            void GetBatteryInfo() const { std::cout << "Battery level: " << BatteryLevel << '/' << BatteryCapacity << '\n'; }
            double BatteryLevel{}, BatteryCapacity{};
        };
    }

    namespace case3
    {
        class BankAccount
        {
        public:
            virtual ~BankAccount() = default;
            virtual void Deposit(double amount) { Balance += amount; }
            virtual void Withdraw(double amount) { Balance -= amount; }
            virtual void Transfer(BankAccount &target, double amount)
            {
                Withdraw(amount);
                target.Deposit(amount);
            }
            virtual std::string GetAccountInfo() const
            {
                return "Account: " + AccountNumber + " with balance: " + std::to_string(Balance);
            }
            virtual void UpdateAccountDetails() const { std::cout << "Updating account details for " << AccountNumber << '\n'; }
            std::string AccountNumber{"generated-account-id"};
            double Balance{};
        };
        class FrozenAccount : public BankAccount
        {
        public:
            void Withdraw(double) override {}
            void Deposit(double) override { std::cout << "Cannot deposit to a frozen account " << AccountNumber << '\n'; }
            void Unfreeze() { IsFrozen = false; }
            void Freeze() { IsFrozen = true; }
            bool IsFrozen{true};
        };
    }
}
