//# EarthMagneticMachine.h: Calculates magnetic field in a direction  
//# Copyright (C) 1998
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id$

#if !defined(AIPS_EARTHMAGNETICMACHINE_H)
#define AIPS_EARTHMAGNETICMACHINE_H

//# Includes
#include <aips/aips.h>
#include <aips/Measures.h>
#include <aips/Measures/MCDirection.h>
#include <aips/Measures/MVPosition.h>
#include <aips/Measures/EarthField.h>
#include <aips/Measures/MVEarthMagnetic.h>

//# Forward Declarations
class MeasFrame;
class MPosition;
class MEpoch;

template <class T> class Vector;

// <summary> Calculates magnetic field in a direction </summary>

// <use visibility=export>

// <reviewed reviewer="" date="yyyy/mm/dd" tests="tEarthMagneticMachine.cc" demos="">
// </reviewed>

// <prerequisite>
//   <li> <linkto class=MEarthMagnetic>MEarthMagnetic</linkto> class
//   <li> <linkto class=MDirection>MDirection</linkto> class
// </prerequisite>
//
// <etymology>
// From Earth' magnetic Field and machinery
// </etymology>
//
// <synopsis>
// The construction of an EarthMagneticMachine class object creates a
// machine that can
// calculate the magnetic field in an arbitrary direction.
//
// The constructors need a reference code (and possibly frame) input 
// <linkto class=MDirection>MDirection::Ref</linkto>  to specify how the
// the input coordinates have to be interpreted (e.g. MDirection::HADEC).
// It also needs an altitude above the Earth for which the field has to be
// calculated. The position on Earth can be given as either a 
// <linkto class=MPosition>position</linkto>, or as a frame containing the
// position. In the latter case the frame will also be used in the
// coordinate transformations.
//
// Once the EarthMagneticMachine has been established, it can be used to
// calculate
// the field by the <em>calculate(MVDirection)</em> method. A variety of
// get methods let you obtain e.g. the field along the line of sight, the
// longitude of the point for which the field was calculated (e.g. the
// sub-ionospheric point). 
// </synopsis>
//
// <example>
// <srcblock>
//	// Define a time/position frame
//	MEpoch epo(MVEpoch(MVTime(98,5,16,0.5).day()));
//	MPosition pos;
//	MeasTable::Observatory(pos, "ATCA");
//	MeasFrame frame(epo, pos);
//	// Note that e.g. the time in the frame can be changed later
//	// Set up a machine
//	EarthMagneticMachine exec(MDirection::B1950, Quantity(200, "km"), frame);
//	// Given a current observational direction
//	MDirection indir(Quantity(3.25745692, "rad"),
//		   	 Quantity(0.040643336,"rad"),
//		   	 MDirection::Ref(MDirection::B1950));
//	// The field in this direction is calculated
//	exec.calculate(indir.getValue());
//	// Show some data
//	cout << "Parallel field: " << exec.getLOSField() << " nT" << endl;
//	cout << "Sub-ionosphere long: " << exec.getLong("deg") << endl;
// </srcblock>
// </example>
//
// <motivation>
// To aid calculating fields in a simple way.
// </motivation>
//
// <todo asof="1998/01/21">
//   <li> add more get() values if necessary
// </todo>

class EarthMagneticMachine {
public:
  //# Constructors
  // Construct an empty machine (probably not usable unles set() used)
  EarthMagneticMachine();
  // Construct a machine from the input values
  // <thrown>
  //   <li> AipsError if frame does not contain position and time
  // </thrown>
  // <group>
  EarthMagneticMachine(const MDirection::Ref &in, const Quantum<Double> &hgt,
		       MeasFrame &frame);
  EarthMagneticMachine(const MDirection::Ref &in, const Quantum<Double> &hgt,
		       const MPosition &pos, const MEpoch &tm);
  // </group>
  // Copy constructor
  EarthMagneticMachine(const EarthMagneticMachine &other);
  // Copy assignments
  EarthMagneticMachine &operator=(const EarthMagneticMachine &other);

  //# Destructor
  ~EarthMagneticMachine();

  //# Operators
  // Return line-of-sight field (nT or given units) (from previous calculate
  // if no direction given)
  // <group>
  Double operator()();
  Quantum<Double> operator()(const Unit &un);
  Double operator()(const MVDirection &in);
  Quantum<Double> operator()(const MVDirection &in, const Unit &un);
  // </group>

  //# Member functions
  // Set or reset part of the machine
  // <group>
  void set(const MDirection::Ref &in);
  void set(const Quantum<Double> &hgt);
  void set(MeasFrame &frame);
  void set(const MPosition &pos);
  void set(const MEpoch &tm);
  //</group>
  // Calculate a value
  Bool calculate(const MVDirection &in);
  // Return data
  // <group>
  // Line-of-sight field in nT
  // <group>
  Double getLOSField();
  Double getLOSField(const MVDirection &in);
  // </group>
  // Line-of-sight field in specified units (e.g. G)
  // <group>
  Quantum<Double> getLOSField(const Unit &un);
  Quantum<Double> getLOSField(const MVDirection &in, const Unit &un);
  // </group>
  // Field (in nT, in ITRF)
  // <group>
  const MVEarthMagnetic &getField();
  const MVEarthMagnetic &getField(const MVDirection &in);
  // </group>
  // Longitude (rad)
  // <group>
  Double getLong();
  Double getLong(const MVDirection &in);
  // </group>
  // Longitude in units (e.g. deg)
  // <group>
  Quantum<Double> getLong(const Unit &un);
  Quantum<Double> getLong(const MVDirection &in, const Unit &un);
  // </group>
  // Position point
  // <group>
  const MVPosition &getPosition();
  const MVPosition &getPosition(const MVDirection &in);
  // </group>
  // </group>
  // Recalculate the machinery
  void reCalculate();

private:

  //# Data
  // Input direction reference
  MDirection::Ref inref_p;
  // Height (m)
  Double hgt_p;
  // Observatory position
  MVPosition pos_p;
  // Distance to Earth centre
  Double posl_p;
  // Distance squared to sub-point
  Double subl_p;
  // Epoch
  Double epo_p;
  // Conversion engine
  MDirection::Convert conv_p;
  // Input position
  MVDirection in_p;
  // Extension calculated
  // <group>
  Bool fex_p;
  Bool pex_p;
  // </group>
  // Position sub-point
  MVPosition sub_p;
  // Earth field calculator
  EarthField fldc_p;
  // Magnetic field
  MVEarthMagnetic fld_p;
  // Line-of-sight field
  Double los_p;
  // Field position
  Vector<Double> pl_p;
  // Fields filled
  Int fil_p;
  // Init done
  Bool inx_p;
  // Calc done
  Bool clx_p;

  //# Private Member Functions
  // Initialise machinery
  void init();
  // Copy data members
  void copy(const EarthMagneticMachine &other);
};

#endif
