//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Jun 14 15:33:00 2011 by ROOT version 5.31/01)
//      from the StreamerInfo in file http://root.cern.ch/files/atlasFlushed.root
//////////////////////////////////////////////////////////


#ifndef Rec__TrackParticleTruthCollection_p1_h
#define Rec__TrackParticleTruthCollection_p1_h
namespace Rec {
class TrackParticleTruthCollection_p1;
} // end of namespace.

#include "DataLink_p1.h"
#include "Riostream.h"
#include <vector>
#include "Rec__TrackParticleTruthCollection_p1.h"
#include "HepMcParticleLink_p1.h"

namespace Rec {
class TrackParticleTruthCollection_p1 {

public:
// Nested classes forward declaration.
class Entry;

public:
// Nested classes declaration.
class Entry {

public:
// Nested classes declaration.

public:
// Data Members.
   unsigned int index;       //
   float        probability;    //
   HepMcParticleLink_p1 particle;       //

   Entry();
   Entry(const Entry & );
   virtual ~Entry();

};

public:
// Data Members.
   DataLink_p1 m_trackCollectionLink;    //
   vector<Rec::TrackParticleTruthCollection_p1::Entry> m_entries;                //(Rec::TrackParticleTruthCollection_p1::Entry)

   TrackParticleTruthCollection_p1();
   TrackParticleTruthCollection_p1(const TrackParticleTruthCollection_p1 & );
   virtual ~TrackParticleTruthCollection_p1();

};
} // namespace
#endif