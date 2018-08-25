/*
 * access_to_bits.h
 *
 * Created: 17.08.2018
 * Author: Alexander Velilyaev
 * Contact: Alexandervelilyaev@gmail.com
 *
 * This file allows to work with any bit separately
 */ 


#ifndef ACCESS_TO_BITS_H_
#define ACCESS_TO_BITS_H_

#define SET_BIT(PORT, POS, VALUE) PORT = (PORT & ~(1 << POS)) | (VALUE << POS)
#define GET_BIT(PORT, POS) (PORT & (1 << POS)) >> POS

#endif /* ACCESS_TO_BITS_H_ */