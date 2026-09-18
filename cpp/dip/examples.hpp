#pragma once

#include <algorithm>
#include <chrono>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace ConsoleApp2::dip
{
    namespace example
    {
        class SamsungTv
        {
        public:
            explicit SamsungTv(std::string model) : Model(std::move(model)) {}
            void TurnOn() const { std::cout << "SamsungTV " << Model << " включен\n"; }
            void TurnOff() const { std::cout << "SamsungTV " << Model << " выключен\n"; }
            void ChangeChannel(int channel) { CurrentChannel = channel; }
            void AdjustVolume(int volume) { Volume = volume; }
            void GetStatus() const { std::cout << "Статус: Модель=" << Model << ", Канал=" << CurrentChannel << ", Громкость=" << Volume << '\n'; }
            std::string Model;
            int CurrentChannel{1}, Volume{10};
        };
        class SamsungTvRemote
        {
        public:
            explicit SamsungTvRemote(SamsungTv &tv) : tv_(tv) {}
            void RemoteTurnOn() const { tv_.TurnOn(); }
            void RemoteTurnOff() const { tv_.TurnOff(); }
            void RemoteSetChannel(int channel) { tv_.ChangeChannel(channel); }
            void RemoteVolumeUp() { tv_.AdjustVolume(tv_.Volume + 1); }
            void RemoteVolumeDown() { tv_.AdjustVolume(tv_.Volume - 1); }

        private:
            SamsungTv &tv_;
        };
        class PhilipsTv
        {
        public:
            explicit PhilipsTv(std::string model) : Model(std::move(model)) {}
            void On() const { std::cout << "PhilipsTV " << Model << " включен\n"; }
            void Off() const { std::cout << "PhilipsTV " << Model << " выключен\n"; }
            void ChangeChannel(int channel) { CurrentChannel = channel; }
            void AdjustVolume(int volume) { Volume = std::clamp(volume, 0, 100); }
            void GetData() const { std::cout << "Интернал инфо: Модель=" << Model << ", Канал=" << CurrentChannel << ", Громкость=" << Volume << '\n'; }
            std::string Model;
            int CurrentChannel{}, Volume{50};
        };
    }

    namespace cooler_example
    {
        class ITv
        {
        public:
            virtual ~ITv() = default;
            virtual void TurningOn() = 0;
            virtual void TurningOff() = 0;
            virtual void PutChannel(int channel) = 0;
            virtual void IncreaseVolume(int amount) = 0;
            virtual void GetInfo() const = 0;
        };
        class SamsungTvAdapter : public ITv
        {
        public:
            explicit SamsungTvAdapter(example::SamsungTv &tv) : tv_(tv) {}
            void TurningOn() override { tv_.TurnOn(); }
            void TurningOff() override { tv_.TurnOff(); }
            void PutChannel(int channel) override { tv_.ChangeChannel(channel); }
            void IncreaseVolume(int amount) override { tv_.AdjustVolume(tv_.Volume + amount); }
            void GetInfo() const override { tv_.GetStatus(); }

        private:
            example::SamsungTv &tv_;
        };
        class UniversalRemote
        {
        public:
            explicit UniversalRemote(ITv &tv) : tv_(tv) {}
            void TurnOnTv() { tv_.TurningOn(); }
            void TurnOffTv() { tv_.TurningOff(); }
            void SetChannel(int channel) { tv_.PutChannel(channel); }
            void IncreaseVolume() { tv_.IncreaseVolume(1); }
            void DecreaseVolume() { tv_.IncreaseVolume(-1); }

        private:
            ITv &tv_;
        };
    }

    namespace case1
    {
        class EmailSender
        {
        public:
            EmailSender(std::string server, int port) : SmtpServer(std::move(server)), Port(port) {}
            void Connect() const { std::cout << "Connecting to SMTP server " << SmtpServer << ':' << Port << '\n'; }
            void SendEmail(const std::string &recipient, const std::string &subject, const std::string &) const
            {
                std::cout << "Sending email to " << recipient << " with subject " << subject << '\n';
            }
            void Disconnect() const { std::cout << "Disconnecting from SMTP server " << SmtpServer << '\n'; }
            void LogEmail(const std::string &log) const { std::cout << "Logging email: " << log << '\n'; }
            std::string SmtpServer;
            int Port;
        };
        class Notifier
        {
        public:
            explicit Notifier(std::string name)
                : NotifierName(std::move(name)), emailSender_("smtp.example.com", 25) {}
            void NotifyByEmail(const std::string &recipient, const std::string &subject,
                               const std::string &message) const
            {
                emailSender_.Connect();
                emailSender_.SendEmail(recipient, subject, message);
                emailSender_.Disconnect();
            }
            void LogNotification(const std::string &log) const { emailSender_.LogEmail(log); }
            void UpdateNotifierName(std::string name) { NotifierName = std::move(name); }
            void ShowNotifierInfo() const { std::cout << "Notifier: " << NotifierName << '\n'; }
            std::string NotifierName;

        private:
            EmailSender emailSender_;
        };
    }

    namespace case2
    {
        class Logger
        {
        public:
            explicit Logger(std::string path) : FilePath(std::move(path)) {}
            void WriteLog(const std::string &log) const { std::cout << "Writing log to file " << FilePath << ": " << log << '\n'; }
            void ClearLog() const { std::cout << "Clearing log file " << FilePath << '\n'; }
            void ArchiveLog() const { std::cout << "Archiving log file " << FilePath << '\n'; }
            void GetLogStatus() const { std::cout << "Checking log status for file " << FilePath << '\n'; }
            std::string FilePath;
        };
        class UserActivity
        {
        public:
            explicit UserActivity(std::string userName)
                : UserName(std::move(userName)), logger_("user_activity.log") {}
            void RecordActivity(const std::string &activity)
            {
                ++ActivityCount;
                logger_.WriteLog("User " + UserName + " did " + activity + ". Count: " + std::to_string(ActivityCount));
            }
            void ResetActivityCount()
            {
                ActivityCount = 0;
                logger_.WriteLog("Reset activity count for " + UserName);
            }
            void ArchiveActivity() const { logger_.ArchiveLog(); }
            void DisplayActivity() const { std::cout << "User " << UserName << " has " << ActivityCount << " activities recorded.\n"; }
            std::string UserName;
            int ActivityCount{};

        private:
            Logger logger_;
        };
    }

    namespace case3
    {
        class MySqlDatabase
        {
        public:
            explicit MySqlDatabase(std::string connectionString) : connectionString_(std::move(connectionString)) {}
            void Connect() const
            {
                std::this_thread::sleep_for(std::chrono::seconds(3));
                std::cout << "Connection done " << connectionString_ << '\n';
            }
            void Disconnect() const {}
            std::vector<std::string> GetRecords() const { return {"data1", "data2"}; }
            void WriteLogEntry(const std::string &entry) const { std::ofstream("log.txt") << entry; }

        private:
            std::string connectionString_;
        };
        class ReportGenerator
        {
        public:
            ReportGenerator() : database_("mysql://dsadlkasjdklasjdaklsjd") {}
            void GenerateReport()
            {
                database_.Connect();
                reportData_ = database_.GetRecords();
                ProcessData();
                const auto lines = FormatReport();
                std::string report;
                for (std::size_t i = 0; i < lines.size(); ++i)
                    report += (i == 0 ? "" : ";") + lines[i];
                SaveReport(report);
            }
            void SaveReport(const std::string &text) const { database_.WriteLogEntry(text); }

        private:
            void ProcessData()
            {
                if (reportData_.size() > 100)
                    reportData_.resize(100);
            }
            std::vector<std::string> FormatReport() const
            {
                std::vector<std::string> result;
                for (auto item : reportData_)
                {
                    std::transform(item.begin(), item.end(), item.begin(),
                                   [](unsigned char c)
                                   { return static_cast<char>(std::toupper(c)); });
                    result.push_back("Item: " + item);
                    std::cout << result.back() << '\n';
                }
                return result;
            }
            MySqlDatabase database_;
            std::vector<std::string> reportData_;
        };
    }
}
