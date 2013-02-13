export gtm_chset="UTF-8"
export gtm_noundef="TRUE"
export TZ="GTM"

source /usr/local/gtm/gtmprofile

export GTMCI=${HOME}/javam/gtm_ci_old/calltab.ci
export gtmroutines="${HOME}/javam/gtm_ci_old ${gtmroutines}"
export LD_LIBRARY_PATH=${gtm_dist}:${LD_LIBRARY_PATH}

java -Djava.library.path=${HOME}/javam/gtm_ci_old -jar JavaM.jar $1 $2 $3 $4 $5 $6 $7

stty sane
