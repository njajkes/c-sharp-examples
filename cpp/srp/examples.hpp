#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace ConsoleApp2::srp
{

    namespace example
    {
        struct Course
        {
            explicit Course(std::string courseName) : name(std::move(courseName)) {}
            std::string name;
        };

        class CourseManager
        {
        public:
            void CreateCourse(const std::string &courseName) { courses_.emplace_back(courseName); }
            void RemoveCourse(const std::string &courseName)
            {
                const auto firstRemoved = std::remove_if(
                    courses_.begin(), courses_.end(),
                    [&](const Course &course)
                    { return course.name == courseName; });
                courses_.erase(firstRemoved, courses_.end());
            }
            std::string GenerateReport() const
            {
                std::ostringstream report;
                for (std::size_t i = 0; i < courses_.size(); ++i)
                {
                    report << i + 1 << " - " << courses_[i].name;
                }
                return report.str();
            }

        private:
            std::vector<Course> courses_;
        };
    }

    namespace cooler_example
    {
        using Course = example::Course;

        class CourseManager
        {
        private:
            std::vector<Course> courses_;

        public:
            void CreateCourse(const std::string &courseName) { courses_.emplace_back(courseName); }
            void RemoveCourse(const std::string &courseName)
            {
                const auto firstRemoved = std::remove_if(
                    courses_.begin(), courses_.end(),
                    [&](const Course &course)
                    { return course.name == courseName; });
                courses_.erase(firstRemoved, courses_.end());
            }
            const std::vector<Course> &GetCourses() const { return courses_; }
        };

        class Report
        {
        public:
            std::string GeneratePlainReport(const std::vector<Course> &courses) const
            {
                std::ostringstream report;
                for (std::size_t i = 0; i < courses.size(); ++i)
                {
                    report << i + 1 << " - " << courses[i].name;
                }
                return report.str();
            }
        };
    }

    namespace case1
    {
        class Channel
        {
        public:
            explicit Channel(std::string host) : host_(std::move(host)) {}
            void SendMessage(const std::string &source, const std::string &destination,
                             const std::string &message) const
            {
                std::cout << "[SEND " << host_ << "] " << source << " - " << destination
                          << ": " << message << ";\n";
            }

        private:
            std::string host_;
        };

        class Client
        {
        public:
            Client(std::string id, std::string fullName, Channel &channel)
                : id_(std::move(id)), fullName_(std::move(fullName)), channel_(channel) {}
            const std::string &Name() const { return fullName_; }
            std::string GetCurrentRenderedState() const
            {
                return "<id>" + id_ + "</id>\n<fullname>" + fullName_ + "</fullname>";
            }
            void SendMessageToClient(const Client &destination, const std::string &message) const
            {
                channel_.SendMessage(Name(), destination.Name(), message);
            }

        private:
            std::string id_;
            std::string fullName_;
            Channel &channel_;
        };
    }

    namespace case2
    {
    class User
    {
    public:
        void Register(std::string name, std::string email, std::string password)
        {
            Name = std::move(name);
            Email = std::move(email);
            Password = std::move(password);
            std::cout << "User registered!\n";
        }
        void PrintUserInfo() const { std::cout << "User: " << Name << " Email: " << Email << '\n'; }
        void ChangePassword(std::string password)
        {
            Password = std::move(password);
            std::cout << "Password changed!\n";
        }
        void SendEmail(const std::string &message) const
        {
            std::cout << "Email sent to " << Email << ": " << message << '\n';
        }

        std::string Name, Email, Password;
    };

    class App
    {
    public:
        void Execute() const
        {
            User user;
            user.Register("Tim", "tim@example.com", "123456");
            user.PrintUserInfo();
            user.SendEmail("Hello!");
        }
    };
    }

    namespace case3
    {
        class Order
        {
        public:
            void AddItem(std::string item) { Items.push_back(std::move(item)); }
            void SaveToDatabase() const { std::cout << "Order saved to database!\n"; }
            void PrintOrder() const
            {
                std::cout << "Order #" << OrderId << '\n';
                for (const auto &item : Items)
                    std::cout << " - " << item << '\n';
            }
            void SendOrderConfirmation() const { std::cout << "Order confirmation email sent!\n"; }

            int OrderId{};
            std::vector<std::string> Items;
        };
    }

    namespace case4
    {
        class Employee
        {
        public:
            void SetSalary(double amount) { Salary = amount; }
            void PrintInfo() const { std::cout << "Employee: " << Name << " Salary: $" << Salary << '\n'; }
            void SaveToFile() const
            {
                std::ofstream("employee.txt") << Name << " - " << Salary;
                std::cout << "Employee saved to file!\n";
            }
            void LoadFromFile() const
            {
                std::ifstream input("employee.txt");
                std::ostringstream data;
                data << input.rdbuf();
                std::cout << "Loaded: " << data.str() << '\n';
            }

            std::string Name;
            double Salary{};
        };
        
    }

}
