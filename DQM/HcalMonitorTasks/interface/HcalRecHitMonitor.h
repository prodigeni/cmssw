#ifndef DQM_HCALMONITORTASKS_HCALRECHITMONITOR_H
#define DQM_HCALMONITORTASKS_HCALRECHITMONITOR_H

#include "DQM/HcalMonitorTasks/interface/HcalBaseMonitor.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "CondFormats/HcalObjects/interface/HcalChannelStatus.h"
#include "CondFormats/HcalObjects/interface/HcalChannelQuality.h"

#include <cmath>
#include <iostream>
#include <fstream>

#define RECHITMON_TIME_MIN -250
#define RECHITMON_TIME_MAX 250

/** \class HcalRecHitMonitor
  *
  * $Date: 2009/12/03 14:45:15 $
  * $Revision: 1.39 $
  * \author J. Temple - Univ. of Maryland
  */


class HcalRecHitMonitor: public HcalBaseMonitor {

 public:
  HcalRecHitMonitor();

  ~HcalRecHitMonitor();

  void setup(const edm::ParameterSet& ps, DQMStore* dbe);
  void beginRun();
  void done();
  void clearME(); // overrides base class function
  void reset();
  void zeroCounters();
 
  void processEvent(const HBHERecHitCollection& hbHits,
                    const HORecHitCollection& hoHits,
                    const HFRecHitCollection& hfHits,
		    int CalibType,
		    int BCN,
		    const edm::Event& iEvent
		    );

  void processEvent_rechit( const HBHERecHitCollection& hbheHits,
			    const HORecHitCollection& hoHits,
			    const HFRecHitCollection& hfHits,
			    bool passedHLT,
			    int BCN);

  void endLuminosityBlock();
 private:
  
  void fill_Nevents();
  bool rechit_makeDiagnostics_;

  int rechit_checkNevents_;  // specify how often to fill histograms

  double energyThreshold_;
  double HBenergyThreshold_;
  double HEenergyThreshold_;
  double HOenergyThreshold_;
  double HFenergyThreshold_;
  double ZDCenergyThreshold_;

  double rechit_minErrorFlag_; // minimum error rate needed to dump out bad bin info 

  // Basic Histograms
  EtaPhiHists OccupancyByDepth;
  EtaPhiHists OccupancyThreshByDepth;

  EtaPhiHists SumEnergyByDepth;
  EtaPhiHists SqrtSumEnergy2ByDepth;
  EtaPhiHists SumEnergyThreshByDepth;
  EtaPhiHists SumTimeByDepth;
  EtaPhiHists SumTimeThreshByDepth;


  unsigned int occupancy_[85][72][4]; // will get filled when rechit found
  unsigned int occupancy_thresh_[85][72][4]; // filled when above given energy
  double energy_[85][72][4]; // will get filled when rechit found
  double energy2_[85][72][4]; // will get filled when rechit found
  double energy_thresh_[85][72][4]; // filled when above given  
  double time_[85][72][4]; // will get filled when rechit found
  double time_thresh_[85][72][4]; // filled when above given energy

  double HBenergy_[200];
  double HBenergy_thresh_[200];
  double HBtime_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HBtime_thresh_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HB_occupancy_[2593];
  double HB_occupancy_thresh_[2593];
  double HEenergy_[200];
  double HEenergy_thresh_[200];
  double HEtime_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HEtime_thresh_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HE_occupancy_[2593];
  double HE_occupancy_thresh_[2593];
  double HOenergy_[200];
  double HOenergy_thresh_[200];
  double HOtime_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HOtime_thresh_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HO_occupancy_[2161];
  double HO_occupancy_thresh_[2161];
  double HFenergy_[200];
  double HFenergy_thresh_[200];
  double HFtime_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HFtime_thresh_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HFenergyLong_[200];
  double HFenergyLong_thresh_[200];
  double HFtimeLong_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HFtimeLong_thresh_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HFenergyShort_[200];
  double HFenergyShort_thresh_[200];
  double HFtimeShort_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HFtimeShort_thresh_[RECHITMON_TIME_MAX-RECHITMON_TIME_MIN];
  double HF_occupancy_[1729];
  double HF_occupancy_thresh_[1729];
  double HFlong_occupancy_[865];
  double HFlong_occupancy_thresh_[865];
  double HFshort_occupancy_[865];
  double HFshort_occupancy_thresh_[865];

  int HEflagcounter_[32];
  int HBflagcounter_[32];
  int HOflagcounter_[32];
  int HFflagcounter_[32];

  // Diagnostic plots
  MonitorElement* h_HBEnergy;
  MonitorElement* h_HBThreshEnergy;
  MonitorElement* h_HBTotalEnergy;
  MonitorElement* h_HBThreshTotalEnergy;
  MonitorElement* h_HBTime;
  MonitorElement* h_HBThreshTime;
  MonitorElement* h_HBOccupancy;
  MonitorElement* h_HBThreshOccupancy;

  MonitorElement* h_HEEnergy;
  MonitorElement* h_HEThreshEnergy;
  MonitorElement* h_HETotalEnergy;
  MonitorElement* h_HEThreshTotalEnergy;
  MonitorElement* h_HETime;
  MonitorElement* h_HEThreshTime;
  MonitorElement* h_HEOccupancy;
  MonitorElement* h_HEThreshOccupancy;

  MonitorElement* h_HOEnergy;
  MonitorElement* h_HOThreshEnergy;
  MonitorElement* h_HOTotalEnergy;
  MonitorElement* h_HOThreshTotalEnergy;
  MonitorElement* h_HOTime;
  MonitorElement* h_HOThreshTime;
  MonitorElement* h_HOOccupancy;
  MonitorElement* h_HOThreshOccupancy;

  MonitorElement* h_HFEnergy;
  MonitorElement* h_HFThreshEnergy;
  MonitorElement* h_HFTotalEnergy;
  MonitorElement* h_HFThreshTotalEnergy;
  MonitorElement* h_HFTime;
  MonitorElement* h_HFThreshTime;
  MonitorElement* h_HFOccupancy;
  MonitorElement* h_HFThreshOccupancy;

  MonitorElement* h_HBflagcounter;
  MonitorElement* h_HEflagcounter;
  MonitorElement* h_HOflagcounter;
  MonitorElement* h_HFflagcounter;
  
  
  double collisionHFthresh_;
  double collisionHEthresh_;
  MonitorElement* h_HFtimedifference;
  MonitorElement* h_HFenergydifference;
  MonitorElement* h_HEtimedifference;
  MonitorElement* h_HEenergydifference;

  MonitorElement* h_HFrawenergydifference;
  MonitorElement* h_HErawenergydifference;
  MonitorElement* h_HFrawtimedifference;
  MonitorElement* h_HErawtimedifference;

  MonitorElement* h_HFnot101timedifference;
  MonitorElement* h_HFnot101energydifference;
  MonitorElement* h_HEnot101timedifference;
  MonitorElement* h_HEnot101energydifference;
  MonitorElement* h_HFnot101rawenergydifference;
  MonitorElement* h_HEnot101rawenergydifference;
  MonitorElement* h_HFnot101rawtimedifference;
  MonitorElement* h_HEnot101rawtimedifference;



  bool HBpresent_, HEpresent_, HOpresent_, HFpresent_;
};

#endif
