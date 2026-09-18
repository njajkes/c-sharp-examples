#pragma once

#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace ConsoleApp2::ocp
{
    namespace example
    {
        class NotificationManager
        {
        public:
            void SendNotification(const std::string &type, const std::string &message)
            {
                if (type == "Email")
                {
                    SendEmail(message);
                }
                else if (type == "SMS")
                {
                    SendSms(message);
                }
            }

        private:
            void SendEmail(const std::string &) {}
            void SendSms(const std::string &) {}
        };
    }

    namespace cooler_example
    {
        class INotification
        {
        public:
            virtual ~INotification() = default;
            virtual void Send(const std::string &message) = 0;
        };
        class EmailNotification : public INotification
        {
        public:
            void Send(const std::string &) override {}
        };
        class SmsNotification : public INotification
        {
        public:
            void Send(const std::string &) override {}
        };
        class NotificationManager
        {
        public:
            explicit NotificationManager(std::vector<std::shared_ptr<INotification>> notifications)
                : notifications_(std::move(notifications)) {}
            void SendAll(const std::string &message) const
            {
                for (const auto &notification : notifications_)
                    notification->Send(message);
            }

        private:
            std::vector<std::shared_ptr<INotification>> notifications_;
        };
    }

    namespace case1
    {
        class ICoolGuy
        {
        public:
            virtual ~ICoolGuy() = default;
            virtual void CallCoolGuy() = 0;
        };

        class User
        {
        public:
            User(bool isSelected, std::string image)
                : isSelected_(isSelected), image_(std::move(image)) {}
            virtual ~User() = default;
            void DrawUser()
            {
                if (isSelected_)
                    DrawEllipseAroundUser();
                if (!image_.empty())
                    DrawImageOfUser();
                if (dynamic_cast<ICoolGuy *>(this) != nullptr)
                    DrawCoolGuyGlasses();
            }

        private:
            void DrawEllipseAroundUser() {}
            void DrawImageOfUser() {}
            void DrawCoolGuyGlasses() {}
            bool isSelected_;
            std::string image_;
        };
    }

    namespace case2
    {
        class Circle
        {
        public:
            explicit Circle(double radius) : Radius(radius) {}
            double GetArea() const { return std::acos(-1.0) * Radius * Radius; }
            double Radius;
        };

        class Rectangle
        {
        public:
            Rectangle(double width, double height) : Width(width), Height(height) {}
            double GetArea() const { return Width * Height; }
            double Width, Height;
        };

        class AreaCalculator
        {
        public:
            double Calculate(const Circle &circle) const { return circle.GetArea(); }
            double Calculate(const Rectangle &rectangle) const { return rectangle.GetArea(); }
        };
    }
}
