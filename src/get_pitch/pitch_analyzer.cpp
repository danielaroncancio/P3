/// @file

#include <iostream>
#include <fstream>
#include <math.h>
#include "pitch_analyzer.h"

using namespace std;

/// Name space of UPC
namespace upc {
  void PitchAnalyzer::autocorrelation(const vector<float> &x, vector<float> &r) const {

    
    for (unsigned int l = 0; l < r.size(); ++l) {
  		/// \TODO Compute the autocorrelation r[l]
      /// \FET AUTOCORRELACIO CALCULADA
      r[l]= 0;
      for(unsigned int n = l; n < x.size(); n++){
        r[l] += x[n]*x[n-l];
      }
      r[l] = r[l]/x.size();  
    }

    if (r[0] == 0.0F) //to avoid log() and divide zero 
      r[0] = 1e-10; 
  }

  void PitchAnalyzer::set_window(Window win_type) {
    if (frameLen == 0)
      return;

    window.resize(frameLen);

    switch (win_type) {
    case HAMMING:
      /// \TODO Implement the Hamming window
      /// Es completamente irrelevante. Senyal peridica envantandada siempre con uno rectangular.
      break;
    case RECT:
    default:
      window.assign(frameLen, 1);
    }
  }

  void PitchAnalyzer::set_f0_range(float min_F0, float max_F0) {
    npitch_min = (unsigned int) samplingFreq/max_F0;
    if (npitch_min < 2)
      npitch_min = 2;  // samplingFreq/2

    npitch_max = 1 + (unsigned int) samplingFreq/min_F0;

    //frameLen should include at least 2*T0
    if (npitch_max > frameLen/2)
      npitch_max = frameLen/2;
  }

  bool PitchAnalyzer::unvoiced(float pot, float r1norm, float rmaxnorm, float ZCR) const {
    /// \TODO Implement a rule to decide whether the sound is voiced or not.
    /// * You can use the standard features (pot, r1norm, rmaxnorm),
    ///   or compute and use other ones.
    /// \FET


float score = 0;
    const float potvalue = -47, r1value = 0.5, zcrvalue= 0.1;

    if (pot < potvalue)
      score += 0.5;
    else if (r1norm < r1value)
      score += 0.5;
    else if (rmaxnorm < this->llindar_rmax)
      score += 0.5;
    
    if (ZCR > zcrvalue)
      score += 0.5;

    if (score >= 1)
      return true; //sordo
    else
      return false; //sonoro
  }

//calul del ZCR
  float PitchAnalyzer::compute_zcr(const vector<float> &x) const {
    float suma=0;
    unsigned int N = x.size();
    
     for(int i=1; i<N; i++){
        if((x[i-1]>=0 && x[i]<=0)||(x[i-1]<=0 && x[i]>=0)){
        suma=suma+1;
        }
        
    }
    return (float) (suma)/(2*(N));
}


  float PitchAnalyzer::compute_pitch(vector<float> & x) const {
    if (x.size() != frameLen)
      return -1.0F;

    //Window input frame
    for (unsigned int i=0; i<x.size(); ++i)
      x[i] *= window[i];

    vector<float> r(npitch_max);

    //Compute correlation
    autocorrelation(x, r);

     // Guardar señal del frame
    ofstream frame_file("frame_signal.txt", ios::app);
    for (float sample : x) {
        frame_file << sample << '\n';
    }
    frame_file.close();

    // Guardar autocorrelación
    ofstream autocorr_file("autocorrelation.txt", ios::app);
    for (float val : r) {
        autocorr_file << val << '\n';
    }
    autocorr_file.close();

    //Compute ZCR
    float ZCR = compute_zcr(x);

    vector<float>::const_iterator iR = r.begin(), iRMax = iR;

    /// \TODO FET
	/// Find the lag of the maximum value of the autocorrelation away from the origin.<br>
	/// Choices to set the minimum value of the lag are:
	///    - The first negative value of the autocorrelation.
	///    - The lag corresponding to the maximum value of the pitch.
    ///	   .
	/// In either case, the lag should not exceed that of the minimum value of the pitch.
      float pot = 10 * log10(r[0]);
    float rMax = r[npitch_min];
    unsigned int lag = npitch_min;
    float r1norm = r[1] / r[0];
    

    for(unsigned int l = npitch_min; l < npitch_max; l++){
      if(r[l]>rMax){
        lag = l;
        rMax = r[l];
      }
    }

  float rmaxnorm = r[lag] / r[0];

  #if 0
    // Guardar els valors en un archiu pot.txt
    ofstream pot_file("pot.txt", ios::app);
    pot_file << pot << '\n';
    pot_file.close();

    ofstream r1norm_file("r1norm.txt", ios::app);
    r1norm_file << r1norm << '\n';
    r1norm_file.close();

    ofstream rmaxnorm_file("rmaxnorm.txt", ios::app);
    rmaxnorm_file << rmaxnorm << '\n';
    rmaxnorm_file.close();

    ofstream zcr_file("zcr.txt", ios::app);
    zcr_file << ZCR << '\n';
    zcr_file.close();
  #endif

    //You can print these (and other) features, look at them using wavesurfer
    //Based on that, implement a rule for unvoiced
    //change to #if 1 and compile
#if 0
    if (r[0] > 0.0F)
      cout << pot << '\t' << r[1]/r[0] << '\t' << r[lag]/r[0] << endl;
#endif
    
    if (unvoiced(pot, r[1]/r[0], r[lag]/r[0], ZCR))
      return 0;
    else
      return (float) samplingFreq/(float) lag;
  }
}
