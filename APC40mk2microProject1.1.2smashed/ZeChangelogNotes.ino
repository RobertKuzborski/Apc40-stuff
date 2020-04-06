//Added New filtering method: mean in read section - and it's efficient asfuck (can't handle more than 2 because of timing) 4 works but glitch sometimes
// Need to leave this check if 0 or if max not to be stuck on 1 or 999
//Interrupt fucks it up, so must be careful!!! definitely add pullup resistor on that one! :)

//New mapping from 10 to 14 bit by adding bitshift both ways +4 and -6 added into one number! works perfectly! 

//Remake Key runtime to more stable one !  <<< BUGFIXTHIS
