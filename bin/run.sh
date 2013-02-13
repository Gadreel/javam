export gtm_chset="UTF-8"
export gtm_noundef="TRUE"
export TZ="GTM"

source /usr/local/gtm/gtmprofile

export GTMCI=${HOME}/javam/gtm_ci/calltab.ci
export gtmroutines="${HOME}/javam/gtm_ci ${gtmroutines}"
export LD_LIBRARY_PATH=${gtm_dist}:${LD_LIBRARY_PATH}

java -Djava.library.path=. -cp JavaM.jar com.divconq.test.Main 

stty sane
