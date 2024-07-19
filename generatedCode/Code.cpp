#include "learning_models/KMEANS/kmeans.h"
#include "learning_models/KDE/kde.h"
#include "learning_models/LOF/lof.h"
#include "learning_models/model.h"
#include "window/window.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>



using namespace std;
using json = nlohmann::json;

class Code{
     static constexpr unsigned int days_to_month[2][12] = {
        // non-leap year
        { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
        // leap year
        { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 },
    };

   static constexpr unsigned int days_of_month[2][12] = {
        // non-leap year
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        // leap-year
        { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    };
    public:
    static bool is_leap_year(unsigned int year) {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

    static unsigned int num_day(unsigned int day, unsigned int month, unsigned int year) {
        auto leap = is_leap_year(year);
        return days_to_month[leap][month - 1] + day;
    }

    static int num_week(int day, int month, int year) {
        struct tm tm_start_year = {0, 0, 12, 1, 0, year - 1900, 0, 0, 0}; // 1st Jan
        struct tm tm_date = {0, 0, 12, day, month - 1, year - 1900, 0, 0, 0}; // given date

        if (mktime(&tm_start_year) != (time_t)-1 && mktime(&tm_date) != (time_t)-1) {
            int days_since_start = tm_date.tm_yday - tm_start_year.tm_yday;
            int weeks_since_start = (tm_start_year.tm_wday + days_since_start + 6) / 7;
            if (tm_start_year.tm_wday == 0) {
                weeks_since_start++;
            }
            return weeks_since_start;
        }
        return 0;
    }

    static int compute_period(const std::string& eventDate, const std::string& period_type) {
        std::tm tm = {};
        std::istringstream ss(eventDate);
        ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");

        if (ss.fail()) {
            throw std::runtime_error("Invalid date format");
        }

        int day = tm.tm_mday;
        int month = tm.tm_mon + 1;
        int year = tm.tm_year + 1900;
        int period = 0;

        if (period_type == "week") {
            int week_num = num_week(day, month, year);
            if (month == 12 && week_num == 1) {
                year += 1;
            } else if (month == 1 && (week_num == 52 || week_num == 53)) {
                year -= 1;
            }
            period = year * 100 + week_num;
        } else if (period_type == "day") {
            int day_num = num_day(day, month, year);
            period = year * 1000 + day_num;
        }

        return period;
    }

        static std::map<string, model*> init_map(double kde_parameters, double kmeans_parameters, int lof_parameters){
            std::map<string, model*> map_classes;
            map_classes.emplace(std::pair<std::string,model*>("kde", new kde(kde_parameters)));
            map_classes.emplace(std::pair<std::string,model*>("kmeans", new kmeans(kmeans_parameters)));
            //map_classes.emplace(std::pair<std::string,model*>("knn", new knn()));
            map_classes.emplace(std::pair<std::string,model*>("lof", new lof(lof_parameters)));
            return map_classes;
        };
        static void formatting_data(std::map<int,std::vector<int>> &data, window1* window,std::string eventDate){
              // Définir un objet de type std::tm pour stocker la date et l'heure
            std::tm tm = {};

            // Utiliser std::istringstream pour lire la chaîne de caractères
            std::istringstream ss(eventDate);
            ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");
            std::time_t time = std::mktime(&tm);
            int value = tm.tm_hour;
            std::string type = window->getType();
      
            if(type == "day"||type == "week"){
                int period = compute_period(eventDate,type);
             
                data[period].push_back(value);
                std::vector<int> periodsToDelete = window->add_period(period);
                if(periodsToDelete.size() != 0 ){
                    for(int p : periodsToDelete){
                        data[p].clear();
                        data.erase(p);
                    }
                }
            }
            if(type == "instance"){
                data[0].push_back(value);
                int sliding_on = window->add_instance(value);
                int slide_size = window->getSliding_size();
                if(sliding_on == 1) {
                    data[0] = vector<int>(data[0].begin()+slide_size,data[0].end());
                }
            }   
        };

        static void majorityVote(vector<int>& labels, vector<tuple<string, int, string>>& alerts, string eventId, string eventDate, int label, int scenario) {
               
                if(labels.size() == 3 && labels.size()!=0) { // Ensure we have exactly 3 elements (scores from kde, kmeans, lof)
                int count = 0; 
                for(int i = 0; i < labels.size(); i++) {
                    if(labels[i] == 1) count++;
                }

                int combinedScore = (count >= 2) ? 1 : 0;
                if(combinedScore == 1) {
                    alerts.push_back(make_tuple(eventId, count, eventDate));
                    //cout << eventId << " is malicious" << endl;
                }
                
                // Create JSON object for the event
                json eventJson;
                eventJson["eventId"] = eventId;
                eventJson["kmeans_score"] = labels[0];
                eventJson["kde_score"] = labels[1];
                eventJson["lof_score"] = labels[2];
                eventJson["combined_score"] = combinedScore;
                eventJson["label"] = label;
                eventJson["scenario"] = scenario;

                // Write JSON object to a file
                ofstream file("events.json", ios::app);
                if (file.is_open()) {
                    file << eventJson.dump() << endl;
                    file.close();
                } else {
                    cerr << "Unable to open file for writing." << endl;
                }

                labels.clear();
            } else {
               // cerr << "Labels vector does not have exactly 3 elements." << endl;
            }
        }

    };
