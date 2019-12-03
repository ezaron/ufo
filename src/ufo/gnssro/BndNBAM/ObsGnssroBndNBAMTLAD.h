/*
 * (C) Copyright 2017-2018 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef UFO_GNSSRO_BNDNBAM_OBSGNSSROBNDNBAMTLAD_H_
#define UFO_GNSSRO_BNDNBAM_OBSGNSSROBNDNBAMTLAD_H_

#include <memory>
#include <ostream>
#include <string>

#include "oops/base/Variables.h"
#include "oops/util/ObjectCounter.h"
#include "ufo/gnssro/BndNBAM/ObsGnssroBndNBAMTLAD.interface.h"
#include "ufo/LinearObsOperatorBase.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace ioda {
  class ObsSpace;
  class ObsVector;
}

namespace ufo {
  class GeoVaLs;
  class ObsBias;
  class ObsDiagnostics;

// -----------------------------------------------------------------------------
// Gnssro BndNBAM observation operator tl/ad
//   -- to reproduce exactly the operational (2019) NBAM
class ObsGnssroBndNBAMTLAD : public LinearObsOperatorBase,
                          private util::ObjectCounter<ObsGnssroBndNBAMTLAD> {
 public:
  static const std::string classname() {return "ufo::ObsGnssroBndNBAMTLAD";}

  ObsGnssroBndNBAMTLAD(const ioda::ObsSpace &, const eckit::Configuration &);
  virtual ~ObsGnssroBndNBAMTLAD();

  // Obs Operators
  void setTrajectory(const GeoVaLs &, const ObsBias &, ObsDiagnostics &) override;
  void simulateObsTL(const GeoVaLs &, ioda::ObsVector &) const override;
  void simulateObsAD(GeoVaLs &, const ioda::ObsVector &) const override;

  // Other
  const oops::Variables & variables() const override {return *varin_;}

  int & toFortran() {return keyOperGnssroBndNBAM_;}
  const int & toFortran() const {return keyOperGnssroBndNBAM_;}

 private:
  void print(std::ostream &) const override;
  F90hop keyOperGnssroBndNBAM_;
  const ioda::ObsSpace& odb_;
  std::unique_ptr<const oops::Variables> varin_;
};

// -----------------------------------------------------------------------------

}  // namespace ufo
#endif  // UFO_GNSSRO_BNDNBAM_OBSGNSSROBNDNBAMTLAD_H_
