set pagination off
set logging on

break range_get if I->curr % 5 == 0
    command 1
    printf "@@@ %d %d %d %d\n", I->start, I->stop, I->step, I->curr
    continue
end

run 1 12 > /dev/null

set logging off
quit
