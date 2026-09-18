#pragma once

#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>

namespace ConsoleApp2::isp
{
    namespace example
    {
        class IUser
        {
        public:
            virtual ~IUser() = default;
            virtual void BanUser() = 0;
            virtual void PrintComment(int postId, const std::string &comment) = 0;
            virtual void ReadComments(int postId) = 0;
            virtual void PostPost(const std::string &content) = 0;
            virtual void EditPost(int postId, const std::string &content) = 0;
            virtual void ReadPost(int postId) = 0;
        };
        class Client : public IUser
        {
        public:
            explicit Client(std::string name) : UserName(std::move(name)) {}
            void BanUser() override {}
            void PrintComment(int postId, const std::string &comment) override { std::cout << "ок, пост: " << postId << ", комм: " << comment << '\n'; }
            void ReadComments(int) override { std::cout << "тут нет ничего, кроме обсуждения крутых кракозябр\n"; }
            void PostPost(const std::string &) override { throw std::logic_error("Not implemented"); }
            void EditPost(int postId, const std::string &content) override
            {
                if (postId == 0)
                    std::cout << "изменен пост 0 с контентом " << content << '\n';
            }
            void ReadPost(int postId) override { std::cout << "Пост " << postId << '\n'; }
            std::string UserName;
        };
        class Admin : public IUser
        {
        public:
            void BanUser() override { std::cout << "BAN\n"; }
            void PrintComment(int, const std::string &) override { throw std::runtime_error("ОШИБКА С ПРАВАМИ АДМИНА"); }
            void ReadComments(int) override { std::cout << "тут нет ничего, кроме обсуждения крутых кракозябр\n"; }
            void PostPost(const std::string &content) override { std::cout << "ок, пост: 0, контент: " << content << '\n'; }
            void EditPost(int, const std::string &content) override { std::cout << "изменен пост 0 с контентом " << content << '\n'; }
            void ReadPost(int postId) override { std::cout << "Пост " << postId << '\n'; }
        };
    }

    namespace cooler_example
    {
        class IUser
        {
        public:
            virtual ~IUser() = default;
            virtual void ReadComments(int) = 0;
            virtual void ReadPost(int) = 0;
        };
        class ICommenter
        {
        public:
            virtual ~ICommenter() = default;
            virtual void PrintComment(int, const std::string &) = 0;
        };
        class IPoster
        {
        public:
            virtual ~IPoster() = default;
            virtual void PostPost(const std::string &) = 0;
        };
        class IPostEditor
        {
        public:
            virtual ~IPostEditor() = default;
            virtual void EditPost(int, const std::string &) = 0;
        };
        class IAdmin
        {
        public:
            virtual ~IAdmin() = default;
            virtual void BanUser() = 0;
        };

        class Client : public IUser, public IPostEditor, public ICommenter
        {
        public:
            explicit Client(std::string name) : UserName(std::move(name)) {}
            void EditPost(int postId, const std::string &content) override
            {
                if (postId == 0)
                    std::cout << content << '\n';
            }
            void PrintComment(int postId, const std::string &comment) override { std::cout << postId << ": " << comment << '\n'; }
            void ReadComments(int) override { std::cout << "тут нет ничего, кроме обсуждения крутых кракозябр\n"; }
            void ReadPost(int postId) override { std::cout << "Пост " << postId << '\n'; }
            std::string UserName;
        };
        class Admin : public IUser, public IAdmin, public IPoster, public IPostEditor
        {
        public:
            void BanUser() override { std::cout << "BAN\n"; }
            void EditPost(int, const std::string &content) override { std::cout << "изменен пост 0 с контентом " << content << '\n'; }
            void PostPost(const std::string &content) override { std::cout << "ок, пост: 0, контент: " << content << '\n'; }
            void ReadComments(int) override { std::cout << "тут нет ничего, кроме обсуждения крутых кракозябр\n"; }
            void ReadPost(int postId) override { std::cout << "Пост " << postId << '\n'; }
        };
    }

    namespace case1
    {
        class IOfficeDevice
        {
        public:
            virtual ~IOfficeDevice() = default;
            virtual void Print(const std::string &document) = 0;
            virtual void Scan(const std::string &document) = 0;
            virtual void Fax(const std::string &document) = 0;
            virtual void Copy(const std::string &document) = 0;
        };
        class BasicPrinter : public IOfficeDevice
        {
        public:
            explicit BasicPrinter(std::string model) : Model(std::move(model)) {}
            void Print(const std::string &document) override { std::cout << "BasicPrinter printing: " << document << '\n'; }
            void Scan(const std::string &) override { throw std::logic_error("BasicPrinter cannot scan documents"); }
            void Fax(const std::string &) override { throw std::logic_error("BasicPrinter cannot fax documents"); }
            void Copy(const std::string &) override { throw std::logic_error("BasicPrinter cannot copy documents"); }
            void Maintenance() const { std::cout << "Performing maintenance on BasicPrinter " << Model << '\n'; }
            std::string Model;
        };
        class AllInOnePrinter : public IOfficeDevice
        {
        public:
            explicit AllInOnePrinter(std::string model) : Model(std::move(model)) {}
            void Print(const std::string &document) override { std::cout << "AllInOnePrinter printing: " << document << '\n'; }
            void Scan(const std::string &document) override { std::cout << "AllInOnePrinter scanning: " << document << '\n'; }
            void Fax(const std::string &document) override { std::cout << "AllInOnePrinter faxing: " << document << '\n'; }
            void Copy(const std::string &document) override { std::cout << "AllInOnePrinter copying: " << document << '\n'; }
            void Calibrate() const { std::cout << "Calibrating printer " << Model << '\n'; }
            std::string Model;
        };
    }

    namespace case2
    {
        class IMultiFunctionDevice
        {
        public:
            virtual ~IMultiFunctionDevice() = default;
            virtual void Call(const std::string &number) = 0;
            virtual void Browse(const std::string &url) = 0;
            virtual void TakePhoto() = 0;
            virtual void SendEmail(const std::string &recipient, const std::string &subject,
                                   const std::string &body) = 0;
        };
        class SmartPhone : public IMultiFunctionDevice
        {
        public:
            SmartPhone(std::string model, std::string os) : Model(std::move(model)), OS(std::move(os)) {}
            void Call(const std::string &number) override { std::cout << "SmartPhone " << Model << " calling " << number << '\n'; }
            void Browse(const std::string &url) override { std::cout << "SmartPhone " << Model << " browsing " << url << '\n'; }
            void TakePhoto() override { std::cout << "SmartPhone " << Model << " takes a high quality photo\n"; }
            void SendEmail(const std::string &recipient, const std::string &, const std::string &) override
            {
                std::cout << "SmartPhone " << Model << " sending email to " << recipient << '\n';
            }
            void PlayMusic() const { std::cout << "SmartPhone " << Model << " is playing music\n"; }
            std::string Model, OS;
        };
        class BasicPhone : public IMultiFunctionDevice
        {
        public:
            explicit BasicPhone(std::string model) : Model(std::move(model)) {}
            void Call(const std::string &number) override { std::cout << "BasicPhone " << Model << " calling " << number << '\n'; }
            void Browse(const std::string &) override { throw std::logic_error("BasicPhone does not support browsing"); }
            void TakePhoto() override { std::cout << "BasicPhone " << Model << " takes a very low quality photo\n"; }
            void SendEmail(const std::string &, const std::string &, const std::string &) override
            {
                throw std::logic_error("BasicPhone does not support sending emails");
            }
            void SendSms(const std::string &recipient, const std::string &) const
            {
                std::cout << "BasicPhone " << Model << " sending SMS to " << recipient << '\n';
            }
            std::string Model;
        };
    }

    namespace case3
    {
        class IFileRoleOperations
        {
        public:
            virtual ~IFileRoleOperations() = default;
            virtual void OpenFile() = 0;
            virtual std::string ReadFile() const = 0;
            virtual void WriteFile(const std::string &content) = 0;
            virtual void ShareFile(const std::string &recipient) = 0;
            virtual void ArchiveFile() = 0;
        };
        class StandardFile : public IFileRoleOperations
        {
        public:
            StandardFile(std::string name, std::string path) : FileName(std::move(name)), FilePath(std::move(path)) {}
            void OpenFile() override { std::cout << "Opening file " << FileName << " at " << FilePath << '\n'; }
            std::string ReadFile() const override { return "Contents of " + FileName; }
            void WriteFile(const std::string &content) override { std::cout << "Writing to file " << FileName << ": " << content << '\n'; }
            void ShareFile(const std::string &recipient) override { std::cout << "Sharing file " << FileName << " with " << recipient << '\n'; }
            void ArchiveFile() override { std::cout << "Archiving file " << FileName << '\n'; }
            void GetFileDetails() const { std::cout << "File details: " << FileName << ", located at " << FilePath << '\n'; }
            std::string FileName, FilePath;
        };
        class ReadOnlyFile : public IFileRoleOperations
        {
        public:
            ReadOnlyFile(std::string name, std::string path) : FileName(std::move(name)), FilePath(std::move(path)) {}
            void OpenFile() override { std::cout << "Opening read-only file " << FileName << " at " << FilePath << '\n'; }
            std::string ReadFile() const override { return "Read-only content from " + FileName; }
            void WriteFile(const std::string &) override { throw std::logic_error("Cannot write to a read-only file " + FileName); }
            void ShareFile(const std::string &) override { throw std::logic_error("Sharing is not supported for " + FileName); }
            void ArchiveFile() override { throw std::logic_error("Archiving is not supported for " + FileName); }
            void GetFileInfo() const { std::cout << "File Info: " << FileName << " at " << FilePath << '\n'; }
            std::string FileName, FilePath;
        };
    }
}
