#!/bin/ksh

# Take a man tree and make an html tree out of it

DOMAIN=$(domainname)
ARCH=$(arch)
 
case ${DOMAIN} in
   acf)     localeo=reo1 ;;
   bwfid)   localeo=reo1 ;;
   chfid)   localeo=neo1 ;;
   hkfid)   localeo=teo1 ;;
   lnfid)   localeo=leo1 ;;
   nyfid)   localeo=neo1 ;;
   psfid)   localeo=leo1 ;;
   sffid)   localeo=neo1 ;;
   tkfid)   localeo=teo1 ;;
   esac

sections="{1,2,3,4,5,6,7,8}"
#from=/usr/man
#to=/u/eo/repository/system/unix/man
from=`pwd`
to=/tmp/man

function disambiguate
{
newbase=${1}
newname="${newbase}.1"
dis=2
while [ -a "${newname}" ]
   do
      newname=$newbase"."$dis
      dis=$(expr $dis + 1)
      done
}

while getopts f:t:l:is:v c
   do
      case $c in
         f) from=$OPTARG ;;
         t) to=$OPTARG ;;
         l) localeo=$OPTARG ;;
         i) indexonly=1 ;;
         s) sections=$OPTARG ;;
         v) verbose=1 ;;
         esac
      done
shift OPTIND-1

if [ "${verbose}" ]
   then
      print "from: $from"
      print "to: $to"
      print "localeo: $localeo"
      print "sections: $sections"
      if [ "${indexonly}" ]
	 then
	    print "indexonly: 1"
	 fi
   fi

cd $from

if [ ! "${indexonly}" ]
   then
      print "Processing the man pages ..."
      for i in man${sections}/*.man
	 do
	    if [ "$verbose" ]
	       then
		  print $i
	       fi
	    # n=${i%.*}
	    bn="$(basename $i .man)"

	    name=${to}/${bn}.html
	    if [ -a "${name}" ]
	       then
		  oldname=$name
		  disambiguate $name
		  name=$newname
		  print "Collision - ${oldname} will be stored as ${name}"
	       fi
	    eqn $i | tbl | nroff -man | rman -f HTML | sed -e "s/MS_LOCAL_HOST/${localeo}/g" > ${name}
	    done
   fi

print "Building the index.html files ..."
cd $to
for i in man${sections}
  do
  if [ "$verbose" ]
      then
      print $i
  fi
  if [ ! -d $i ]
  then
      continue
  fi
  cd $i
  pwd
  rm -f index.html
  echo '<ul>' > ../new.html
  for j in *.html
    do
    bn="$(basename $j .html)"
    if [ "$verbose" ]
	then
	print -n "$j "
    fi

    # get more interesting name for the link labels
    synl="$(egrep -A 1 '<B>.*</B> - .*' $j |sed -e 's/<B>//g' -e 's/<\/B>//g')"
#    echo "### synl = $synl"
    synname="$(echo $synl |cut -d' ' -f1)"
    synopse="$(echo $synl |cut -d' ' -f3-100)"
    print
    print "<li> <a href=$j>$synname</a> - $synopse" >> ../new.html
  done
  echo '</ul>' >> ../new.html
  mv ../new.html index.html
  cd ..
done
