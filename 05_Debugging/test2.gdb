set pagination off
set logging on

set $var = 0

break range_get if $var++ >= 28 && $var <= 36
    command 1
    printf "@@@ %d %d %d %d\n", I->start, I->stop, I->step, I->curr
    continue
end

run -100 100 3 > /dev/null

set logging off
quit