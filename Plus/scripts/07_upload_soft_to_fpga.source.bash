. $(dirname "$(readlink -f "${BASH_SOURCE[0]}")")/00_setup.source.bash

# id
#
# -G, --groups  print all group IDs
# -n, --name    print a name instead of a number, for -ugG
#
# grep
#
# -w, --word-regexp      match only whole words
# -q, --quiet, --silent  suppress all normal output

gr=dialout

if ! id -nG | grep -qw $gr
then
    error "User \"$USER\" is not in \"$gr\" group."  \
        "Run: \"sudo usermod -a -G $gr $USER\","     \
        "then logout, login and try again."
fi

dev=/dev/ttyUSB0

   stty -F $dev raw speed 57600 -crtscts cs8 -parenb -cstopb  \
|| error "USB-to-UART is not connected or is not working"

if [ -f $program_mem32 ]; then
    cat $program_mem32 > $dev
else
    warning "Cannot find \"$program_mem32\", use \"$demo_program_mem32\" instead."
    cat $demo_program_mem32 > $dev
fi
