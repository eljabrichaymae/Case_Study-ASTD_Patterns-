#include "helper.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <atomic>
#include "learning_models/KDE/kde.h"
#include "Code.cpp"
#include "learning_models/KMEANS/kmeans.h"
#include "learning_models/LOF/lof.h"
#include "learning_models/model.h"
#include <Python.h>
enum GuardState
{
  GUARD_NOTSTARTED,
  GUARD_STARTED
};
enum InterruptState
{
  FST,
  SND
};
enum KleeneState
{
  KLEENE_NOTSTARTED,
  KLEENE_STARTED
};
enum ChoiceState
{
  NONE,
  LEFT,
  RIGHT
};
enum AutState
{
  Alert,
  S0
};
struct TState_choice2ASTD2228_guard
{
  AutState  autState;

};
struct TState_Alert
{
  AutState  autState;

};
struct TState_choice_1choiceASTD2228_guard
{
  AutState  autState;
  TState_Alert  ts_Alert;

};
struct TState_choiceASTD2228_guard
{
  ChoiceState  choiceState;
  TState_choice_1choiceASTD2228_guard  ts_choice_1choiceASTD2228_guard;
  TState_choice2ASTD2228_guard  ts_choice2ASTD2228_guard;

};
struct TState_guardASTD2228
{
  GuardState  guardState;
  TState_choiceASTD2228_guard  ts_choiceASTD2228_guard;

};
struct TState_CountOccurrence
{
  AutState  autState;

};
struct TState_pguardASTD2228
{
  TState_CountOccurrence  ts_CountOccurrence;

};
struct TState_ASTD2228
{
  int  count;
  Timer  clock_timed_interrupt;
  InterruptState  interruptState;
  TState_pguardASTD2228  ts_pguardASTD2228;
  TState_guardASTD2228  ts_guardASTD2228;

};
struct TState_TemporalInterval
{
  KleeneState  kleeneState;
  TState_ASTD2228  ts_ASTD2228;

};
struct TState_Data_Parser
{
  AutState  autState;

};
struct TState_majorityVote
{
  AutState  autState;

};
struct TState_training
{
  AutState  autState;

};
struct TState_scoring
{
  AutState  autState;

};
struct TState_ASTD2FF1
{
  Timer  quantified_clock_ASTD2FF1;
  Timer  left_clock_scoring;
  Timer  right_clock_training;
  TState_scoring  ts_scoring;
  TState_training  ts_training;

};
struct TState_detectors
{
  std::string   d;
  std::map<std::string ,model*>  mapdetectors;
  std::map<std::string , TState_ASTD2FF1>  f;

};
struct TState_combination
{
  vector<int>  scores;
  Timer  right_clock_majorityVote;
  Timer  left_clock_detectors;
  TState_detectors  ts_detectors;
  TState_majorityVote  ts_majorityVote;

};
struct TState_CombineModels
{
  Timer  left_clock_combination;
  Timer  right_clock_Data_Parser;
  TState_combination  ts_combination;
  TState_Data_Parser  ts_Data_Parser;

};
struct TState_ASTDF978
{
  std::map<int,std::vector<int>>  data;
  vector<tuple<std::string ,int,std::string >>  alerts;
  window1*  sliding_window;
  Timer  quantified_clock_ASTDF978;
  Timer  right_clock_TemporalInterval;
  Timer  left_clock_CombineModels;
  TState_CombineModels  ts_CombineModels;
  TState_TemporalInterval  ts_TemporalInterval;

};
struct TState_DetectionPattern
{
  int  userId;
  int  lof_parameters;
  json  window_parameters;
  double  kde_parameters;
  double  kmeans_parameters;
  std::map<int, TState_ASTDF978>  f;

};
const std::vector<string>  T_detectors = {json::parse("\"kmeans\""), json::parse("\"kde\""), json::parse("\"lof\"")};
const std::vector<AutState>  shallow_final_scoring = {S0};
const std::vector<AutState>  shallow_final_training = {S0};
const std::vector<AutState>  shallow_final_majorityVote = {S0};
const std::vector<AutState>  shallow_final_Data_Parser = {S0};
const std::vector<AutState>  shallow_final_CountOccurrence = {S0};
const std::vector<AutState>  deep_final_choice_1choiceASTD2228_guard = {S0};
const std::vector<AutState>  shallow_final_Alert = {S0};
const std::vector<AutState>  shallow_final_choice2ASTD2228_guard = {S0};
TState_DetectionPattern  ts_DetectionPattern;
std::mutex  mtx;
std::time_t  step_time = 10000000;
Timer  last_event_time;
Timer  last_step_time;
Timer  exec_start;
bool  continue_signal = 1;

int  forall_detectorsfinal(std::string &  d)
{
	int  exec = 0;
	for(auto const& c : ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f)
	{
		d = c.first;
		if((std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState) !=shallow_final_scoring.end() && std::find(shallow_final_training.begin(), shallow_final_training.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState) !=shallow_final_training.end()))
		{
			exec = exec + 1;
		
		}else 
		{
			return 0;
		
		}
	
	}
	if(exec == T_detectors.size())
	{
		return 1;
	
	}else if(exec < T_detectors.size())
	{
		if((std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), S0) !=shallow_final_scoring.end() && std::find(shallow_final_training.begin(), shallow_final_training.end(), S0) !=shallow_final_training.end()))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int  forall_DetectionPatternfinal(int&  userId)
{
	int  exec = 0;
	for(auto const& c : ts_DetectionPattern.f)
	{
		userId = c.first;
		if(((((forall_detectorsfinal(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d) && (std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState) !=shallow_final_scoring.end() && std::find(shallow_final_training.begin(), shallow_final_training.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState) !=shallow_final_training.end())) && std::find(shallow_final_majorityVote.begin(), shallow_final_majorityVote.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState) !=shallow_final_majorityVote.end()) && std::find(shallow_final_Data_Parser.begin(), shallow_final_Data_Parser.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState) !=shallow_final_Data_Parser.end()) && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState == KLEENE_NOTSTARTED || ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState) !=shallow_final_CountOccurrence.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end())))))))))
		{
			exec = exec + 1;
		
		}
	
	}
	if((exec == ts_DetectionPattern.f.size() && ((((forall_detectorsfinal(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d) && (std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState) !=shallow_final_scoring.end() && std::find(shallow_final_training.begin(), shallow_final_training.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState) !=shallow_final_training.end())) && std::find(shallow_final_majorityVote.begin(), shallow_final_majorityVote.end(), S0) !=shallow_final_majorityVote.end()) && std::find(shallow_final_Data_Parser.begin(), shallow_final_Data_Parser.end(), S0) !=shallow_final_Data_Parser.end()) && (KLEENE_NOTSTARTED == KLEENE_NOTSTARTED || ((FST == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), S0) !=shallow_final_CountOccurrence.end()) || (FST == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))))))))))
	{
		return 1;
	
	}
	return 0;

}

int  exists_DetectionPatternStep_userId(int&  userId)
{
	if(ts_DetectionPattern.f.find(userId) !=ts_DetectionPattern.f.end())
	{
		if((((((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState) !=shallow_final_CountOccurrence.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end())))))) || KLEENE_NOTSTARTED == ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState) && ((FST == FST && ((GUARD_NOTSTARTED == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (GUARD_NOTSTARTED == GUARD_STARTED && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))) || (FST == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))) || ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && ((GUARD_NOTSTARTED == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (GUARD_NOTSTARTED == GUARD_STARTED && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int    Step()
{
	int  exec = 0;
	exec_start.reset_clock();
	for(auto const& _userId_ : ts_DetectionPattern.f)
	{
		ts_DetectionPattern.userId = _userId_.first;
		if(exists_DetectionPatternStep_userId(ts_DetectionPattern.userId))
		{
			if((((((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState) !=shallow_final_CountOccurrence.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end())))))) || KLEENE_NOTSTARTED == ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState) && ((FST == FST && ((GUARD_NOTSTARTED == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (GUARD_NOTSTARTED == GUARD_STARTED && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))) || (FST == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))) || ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && ((GUARD_NOTSTARTED == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (GUARD_NOTSTARTED == GUARD_STARTED && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))))
			{
				if(((((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState) !=shallow_final_CountOccurrence.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end())))))) || KLEENE_NOTSTARTED == ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState) && ((FST == FST && ((GUARD_NOTSTARTED == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (GUARD_NOTSTARTED == GUARD_STARTED && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))) || (FST == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))))
				{
					ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState = KLEENE_STARTED;
					ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState = FST;
					ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.count = 0;
					ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.reset_clock(ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval);
					ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState = S0;
					if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && ((GUARD_NOTSTARTED == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (GUARD_NOTSTARTED == GUARD_STARTED && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))
					{
						Code::alert(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.count);ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState = SND;
						ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState = GUARD_NOTSTARTED;
						ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = NONE;
						if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))))
						{
							ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState = GUARD_STARTED;
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0))
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = LEFT;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = S0;
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))
							{
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}
						
						}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))
						{
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0))
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = LEFT;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = S0;
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))
							{
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}
						
						}
					
					}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))
					{
						if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))))
						{
							ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState = GUARD_STARTED;
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0))
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = LEFT;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = S0;
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))
							{
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}
						
						}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))
						{
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0))
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = LEFT;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = S0;
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))
							{
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}
						
						}
					
					}
					ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.reset_clock();
				}else if(((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && ((GUARD_NOTSTARTED == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (GUARD_NOTSTARTED == GUARD_STARTED && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))))))
				{
					ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState = KLEENE_STARTED;
					if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && ((GUARD_NOTSTARTED == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (GUARD_NOTSTARTED == GUARD_STARTED && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))
					{
						Code::alert(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.count);ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState = SND;
						ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState = GUARD_NOTSTARTED;
						ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = NONE;
						if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))))
						{
							ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState = GUARD_STARTED;
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0))
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = LEFT;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = S0;
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))
							{
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}
						
						}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))
						{
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0))
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = LEFT;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = S0;
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))
							{
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}
						
						}
					
					}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))))
					{
						if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.expired(3.0E11)  && ((NONE == NONE && S0 == S0) || (NONE == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)))))
						{
							ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState = GUARD_STARTED;
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0))
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = LEFT;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = S0;
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))
							{
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}
						
						}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))))
						{
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && S0 == S0))
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState = LEFT;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = S0;
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0))
							{
								if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState == S0)
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.autState = Alert;
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState = S0;
									exec = 1;
								
								}
							
							}
						
						}
					
					}
					ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.reset_clock();
				}
			
			}
			if(exec)
			{
				ts_DetectionPattern.f[ts_DetectionPattern.userId].quantified_clock_ASTDF978.reset_clock();
			}
		
		}
	
	}
	if(exec == 1)
	{
		last_event_time = exec_start;
	
	}
	return exec;

}

int  exists_DetectionPatterne1_userId(int&  p0, std::string &  p1, std::string &  p2)
{
	ts_DetectionPattern.userId = p0;
	if(ts_DetectionPattern.f.find(p0) !=ts_DetectionPattern.f.end())
	{
		if((((((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState) !=shallow_final_CountOccurrence.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end())))))) || KLEENE_NOTSTARTED == ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState) && (FST == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (S0 == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))))
		{
			return 1;
		
		}
	
	}else 
	{
		ts_DetectionPattern.f[ts_DetectionPattern.userId].data = {};
		ts_DetectionPattern.f[ts_DetectionPattern.userId].alerts = {};
		ts_DetectionPattern.f[ts_DetectionPattern.userId].sliding_window = new window1(ts_DetectionPattern.window_parameters);
		ts_DetectionPattern.f[ts_DetectionPattern.userId].quantified_clock_ASTDF978.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].left_clock_CombineModels.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.left_clock_combination.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.right_clock_Data_Parser.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.scores = {};
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.right_clock_majorityVote.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.left_clock_detectors.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.mapdetectors = Code::init_map(ts_DetectionPattern.kde_parameters,ts_DetectionPattern.kmeans_parameters,ts_DetectionPattern.lof_parameters);
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f.clear();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState = S0;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState = S0;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState = KLEENE_NOTSTARTED;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState = FST;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.count = 0;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState = S0;
		if((((((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState) !=shallow_final_CountOccurrence.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end())))))) || KLEENE_NOTSTARTED == ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState) && (FST == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (S0 == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int    e1(int  p0, std::string   p1, std::string   p2)
{
	int  exec = 0;
	exec_start.reset_clock();
	if(exists_DetectionPatterne1_userId(p0, p1, p2))
	{
		if((((((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState) !=shallow_final_CountOccurrence.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end())))))) || KLEENE_NOTSTARTED == ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState) && (FST == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (S0 == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))))
		{
			if(((((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && std::find(shallow_final_CountOccurrence.begin(), shallow_final_CountOccurrence.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState) !=shallow_final_CountOccurrence.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == SND && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_NOTSTARTED && ((NONE == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (NONE == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (NONE == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end()))) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.guardState == GUARD_STARTED && ((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == NONE && (std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end() || std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), S0) !=shallow_final_choice2ASTD2228_guard.end())) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == LEFT && std::find(shallow_final_Alert.begin(), shallow_final_Alert.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice_1choiceASTD2228_guard.ts_Alert.autState) !=shallow_final_Alert.end()) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.choiceState == RIGHT && std::find(shallow_final_choice2ASTD2228_guard.begin(), shallow_final_choice2ASTD2228_guard.end(), ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_guardASTD2228.ts_choiceASTD2228_guard.ts_choice2ASTD2228_guard.autState) !=shallow_final_choice2ASTD2228_guard.end())))))) || KLEENE_NOTSTARTED == ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState) && (FST == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (S0 == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))))
			{
				ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState = KLEENE_STARTED;
				ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState = FST;
				ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.count = 0;
				ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.reset_clock(ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval);
				ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState = S0;
				if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId ))))
				{
					if((ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))
					{
						if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId ))
						{
							ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState = S0;
							exec = 1;
						
						}
					
					}
				
				}
				ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.reset_clock();
			}else if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId ))))
			{
				ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState = KLEENE_STARTED;
				if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState == FST && (ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId ))))
				{
					if((ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.expired(3.0E11) == false  && (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && p2 == "Medium" || p2 == "High" && p0 == ts_DetectionPattern.userId )))
					{
						if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState == S0 && (p2 == "Medium" || p2 == "High") && p0 == ts_DetectionPattern.userId ))
						{
							ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState = S0;
							exec = 1;
						
						}
					
					}
				
				}
				ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.reset_clock();
			}
		
		}
		if(exec)
		{
			ts_DetectionPattern.f[ts_DetectionPattern.userId].quantified_clock_ASTDF978.reset_clock();
		}
	
	}
	if(exec == 1)
	{
		last_event_time = exec_start;
	
	}
	return exec;

}

int  exists_detectorse_d(int&  p0, std::string &  p1, std::string &  p2, std::string &  d)
{
	for(string _d_ : T_detectors)
	{
		d = _d_;
		if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f.find(d) !=ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f.end())
		{
			if(((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState == S0 && p0 == ts_DetectionPattern.userId ) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState == S0 && p0 == ts_DetectionPattern.userId )))
			{
				return 1;
			
			}
		
		}else 
		{
			ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].quantified_clock_ASTD2FF1.reset_clock();
			ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].left_clock_scoring.reset_clock();
			ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].right_clock_training.reset_clock();
			ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState = S0;
			ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState = S0;
			if(((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState == S0 && p0 == ts_DetectionPattern.userId ) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState == S0 && p0 == ts_DetectionPattern.userId )))
			{
				return 1;
			
			}
		
		}
	
	}
	return 0;

}

int  exists_DetectionPatterne_userId(int&  p0, std::string &  p1, std::string &  p2)
{
	ts_DetectionPattern.userId = p0;
	if(ts_DetectionPattern.f.find(p0) !=ts_DetectionPattern.f.end())
	{
		if(((exists_detectorse_d(p0, p1, p2, ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState == S0 && p0 == ts_DetectionPattern.userId )) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState == S0 && p0 == ts_DetectionPattern.userId )))
		{
			return 1;
		
		}
	
	}else 
	{
		ts_DetectionPattern.f[ts_DetectionPattern.userId].data = {};
		ts_DetectionPattern.f[ts_DetectionPattern.userId].alerts = {};
		ts_DetectionPattern.f[ts_DetectionPattern.userId].sliding_window = new window1(ts_DetectionPattern.window_parameters);
		ts_DetectionPattern.f[ts_DetectionPattern.userId].quantified_clock_ASTDF978.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].right_clock_TemporalInterval.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].left_clock_CombineModels.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.left_clock_combination.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.right_clock_Data_Parser.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.scores = {};
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.right_clock_majorityVote.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.left_clock_detectors.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.mapdetectors = Code::init_map(ts_DetectionPattern.kde_parameters,ts_DetectionPattern.kmeans_parameters,ts_DetectionPattern.lof_parameters);
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f.clear();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState = S0;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState = S0;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.kleeneState = KLEENE_NOTSTARTED;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.interruptState = FST;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.count = 0;
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.clock_timed_interrupt.reset_clock();
		ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_TemporalInterval.ts_ASTD2228.ts_pguardASTD2228.ts_CountOccurrence.autState = S0;
		if(((exists_detectorse_d(p0, p1, p2, ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState == S0 && p0 == ts_DetectionPattern.userId )) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState == S0 && p0 == ts_DetectionPattern.userId )))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int    e(int  p0, std::string   p1, std::string   p2)
{
	int  exec = 0;
	exec_start.reset_clock();
	if(exists_DetectionPatterne_userId(p0, p1, p2))
	{
		if(((exists_detectorse_d(p0, p1, p2, ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d) 
		|| (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState == S0 
		&& p0 == ts_DetectionPattern.userId )) 
		|| (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState == S0 
		&& p0 == ts_DetectionPattern.userId )))
		{
			if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState == S0 && p0 == ts_DetectionPattern.userId ))
			{
				if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState == S0 && p0 == ts_DetectionPattern.userId ))
				{
					Code::formatting_data(ts_DetectionPattern.f[ts_DetectionPattern.userId].data,ts_DetectionPattern.f[ts_DetectionPattern.userId].sliding_window,p1);ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.right_clock_Data_Parser.reset_clock();ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_Data_Parser.autState = S0;
					exec = 1;
				
				}
			
			}
			if(exec)
			{
				ts_DetectionPattern.f[ts_DetectionPattern.userId].left_clock_CombineModels.reset_clock();
			}
			if((exists_detectorse_d(p0, p1, p2, ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d) || (ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState == S0 && p0 == ts_DetectionPattern.userId )))
			{
				if(exists_detectorse_d(p0, p1, p2, ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d))
				{
					if(exists_detectorse_d(p0, p1, p2, ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d))
					{
						for(string d : T_detectors)
						{
							ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d = d;
							if(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f.find(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d) ==ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f.end())
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].quantified_clock_ASTD2FF1.reset_clock(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.left_clock_detectors);
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].left_clock_scoring.reset_clock(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.left_clock_detectors);
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].right_clock_training.reset_clock(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.left_clock_detectors);
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState = S0;
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState = S0;
							
							}
							
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState == S0 && p0 == ts_DetectionPattern.userId ))
							{
								if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState == S0 && p0 == ts_DetectionPattern.userId ))
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].sliding_window->fit_partial(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.mapdetectors[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d],ts_DetectionPattern.f[ts_DetectionPattern.userId].data);ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].right_clock_training.reset_clock();ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_training.autState = S0;
									exec = 1;
								
								}
							
							}
							if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState == S0 && p0 == ts_DetectionPattern.userId ))
							{
								if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState == S0 && p0 == ts_DetectionPattern.userId ))
								{
									ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.mapdetectors[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d]->score_partial(p1,p2,ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.scores);ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].left_clock_scoring.reset_clock();ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].ts_scoring.autState = S0;
									exec = 1;
								
								}
							
							}
							if(exec)
							{
								ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.f[ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_detectors.d].quantified_clock_ASTD2FF1.reset_clock();
							}
						
						}
						ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.left_clock_detectors.reset_clock();
					}
				
				}
				if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState == S0 && p0 == ts_DetectionPattern.userId ))
				{
					if((ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState == S0 && p0 == ts_DetectionPattern.userId ))
					{
						Code::majorityVote(ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.scores,ts_DetectionPattern.f[ts_DetectionPattern.userId].alerts,p2,p1);ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.right_clock_majorityVote.reset_clock();ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.ts_combination.ts_majorityVote.autState = S0;
						exec = 1;
					
					}
				
				}
				if(exec)
				{
					ts_DetectionPattern.f[ts_DetectionPattern.userId].ts_CombineModels.left_clock_combination.reset_clock();
				}
			
			}
		
		}
		if(exec)
		{
			ts_DetectionPattern.f[ts_DetectionPattern.userId].quantified_clock_ASTDF978.reset_clock();
		}
	
	}
	if(exec == 1)
	{
		last_event_time = exec_start;
	
	}
	return exec;

}
void* producers_event_func(void* arg)
{
	while (continue_signal)
	{
		int*  argc = (int*) arg;
		mtx.lock();
		Event  _evt = IO::read_event(*argc);
		if(_evt.label.empty())
		{
			continue_signal = 0;
			ERROR_5;
		
		}else if(_evt.label.compare("e1") == 0)
		{
			bool  flag = 0;
			if(_evt.params.size() == 3)
			{
				int  p0;
				p0 = Types::get_int(_evt.params[0], flag);
				std::string   p1;
				p1 = Types::get_str(_evt.params[1]);
				std::string   p2;
				p2 = Types::get_str(_evt.params[2]);
				if((!(flag) && e1(p0, p1, p2)))
				{
					continue;
				}else if(flag)
				{
					ERROR_6;
				
				}else 
				{
					ERROR_2;
				
				}
			
			}else 
			{
				ERROR_7;
			
			}
		
		}else if(_evt.label.compare("e") == 0)
		{
			bool  flag = 0;
			if(_evt.params.size() == 3)
			{
				int  p0;
				p0 = Types::get_int(_evt.params[0], flag);
				std::string   p1;
				p1 = Types::get_str(_evt.params[1]);
				std::string   p2;
				p2 = Types::get_str(_evt.params[2]);
				if((!(flag) && e(p0, p1, p2)))
				{
					continue;
				}else if(flag)
				{
					ERROR_6;
				
				}else 
				{
					ERROR_2;
				
				}
			
			}else 
			{
				ERROR_7;
			
			}
		
		}else 
		{
			ERROR_1;
		
		}
		mtx.unlock();
	
	}
	return NULL;

}
void* producers_Step_func(void* arg)
{
	while (continue_signal)
	{
		if(last_step_time.expired(step_time))
		{
			last_step_time.reset_clock();
			mtx.lock();
			Step();
			mtx.unlock();
		
		}
		std::this_thread::sleep_for(std::chrono::nanoseconds(step_time/1000));
	
	}
	return NULL;

}
int main(int argc, char** argv)
{
	IO::configInputStream(argc, argv);
	ts_DetectionPattern.lof_parameters = lof_parameters;
	ts_DetectionPattern.window_parameters = window_parameters;
	ts_DetectionPattern.kde_parameters = kde_parameters;
	ts_DetectionPattern.kmeans_parameters = kmeans_parameters;
	ts_DetectionPattern.f.clear();
	setenv("PYTHONPATH", "../python_code",0);
	Py_Initialize();
	pthread_t  producers[2];
	pthread_create(& producers[0], NULL, producers_event_func, (void*) &argc);
	pthread_create(& producers[1], NULL, producers_Step_func, NULL);
	pthread_join(producers[0], NULL);
	pthread_join(producers[1], NULL);
	Py_Finalize();
	return 0;

}
