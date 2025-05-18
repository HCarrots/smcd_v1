#include "SingleParticleSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include <cmath>

SingleParticleSD::SingleParticleSD(G4String name, G4int nbins, G4double maxDist)
    : G4VSensitiveDetector(name),
      fNbins(nbins),
      fMaxDist(maxDist),
      fBinWidth(maxDist/nbins),
      fEdepSum(nbins, 0.0),
      fEdepSum2(nbins, 0.0),
      fHitCounts(nbins, 0),
      fMeanEdep(nbins, 0.0),
      fStdError(nbins, 0.0)
{}

SingleParticleSD::~SingleParticleSD()
{
    if(G4Threading::IsMasterThread()) {
        SaveToROOT("single_particle_results.root");
    }
}

void SingleParticleSD::Initialize(G4HCofThisEvent*)
{
    std::fill(fEdepSum.begin(), fEdepSum.end(), 0.0);
    std::fill(fEdepSum2.begin(), fEdepSum2.end(), 0.0);
    std::fill(fHitCounts.begin(), fHitCounts.end(), 0);
}

G4bool SingleParticleSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4double edep = step->GetTotalEnergyDeposit();
    if(edep <= 0.0) return false;

    G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();
    G4double dist = pos.mag();
    if(dist > fMaxDist) return false;

    G4int bin = static_cast<int>(dist / fBinWidth);
    if(bin >= fNbins) bin = fNbins - 1;

    std::lock_guard<std::mutex> lock(fMutex);
    fEdepSum[bin] += edep;
    fEdepSum2[bin] += edep * edep;
    fHitCounts[bin]++;

    return true;
}

void SingleParticleSD::CalculateStatistics()
{
    for(G4int i = 0; i < fNbins; ++i) {
        if(fHitCounts[i] > 0) {
            // Calculate mean
            fMeanEdep[i] = fEdepSum[i] / fHitCounts[i];
            
            // Calculate standard error
            if(fHitCounts[i] > 1) {
                G4double variance = (fEdepSum2[i] - fEdepSum[i]*fMeanEdep[i]) / (fHitCounts[i] - 1);
                fStdError[i] = std::sqrt(variance / fHitCounts[i]);
            }
        }
    }
}

void SingleParticleSD::SaveToROOT(const G4String& filename)
{
    CalculateStatistics();

    TFile file(filename.c_str(), "RECREATE");
    
    // Prepare data
    std::vector<G4double> x(fNbins), y(fNbins), ex(fNbins), ey(fNbins);
    for(G4int i = 0; i < fNbins; ++i) {
        x[i] = (i + 0.5) * fBinWidth;  // Bin center
        ex[i] = fBinWidth / 2.0;       // Half bin width
        y[i] = fMeanEdep[i] / MeV;     // Convert to MeV
        ey[i] = fStdError[i] / MeV;    // Convert to MeV
    }

    // Create and save graph
    TGraphErrors* graph = new TGraphErrors(fNbins, x.data(), y.data(), ex.data(), ey.data());
    graph->SetName("EnergyDeposit");
    graph->SetTitle("Single Particle Energy Deposit;Distance [mm];Energy Deposit [MeV]");
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlue);
    graph->Write();

    // Save plot image
    TCanvas canvas("canvas", "Energy Deposit", 800, 600);
    graph->Draw("AP");
    canvas.SaveAs("energy_deposit.png");

    file.Close();
}
void SingleParticleSD::EndOfEvent(G4HCofThisEvent* hce){};