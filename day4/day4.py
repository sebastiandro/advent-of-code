# Sssssnek
import re
from datetime import datetime
import calendar
from timeit import default_timer as timer

start = timer()
path = 'input.txt'
input_file = open(path, 'r')
lines = input_file.readlines()

parsed_lines = []
worker_matrix = {}

for line in lines:
    date_str = line[1:17]
    date = datetime.strptime(date_str, "%Y-%m-%d %H:%M")
    timestamp = calendar.timegm(date.utctimetuple())
    note = line.split(']')[1]
    parsed_lines.append((timestamp, note.rstrip(), date_str))

parsed_lines.sort(key=lambda x: x[0])

current_guard_id = 0
fell_asleep_at_minute = 0
woke_up_at_minute = 0

for line in parsed_lines:
    note = line[1]
    minute = note[2][1:3]

    if (note[1] == 'G'):
        current_guard_id = int(note[note.find("#")+1:note.find("#")+5])
        if current_guard_id not in worker_matrix:
            worker_matrix[current_guard_id] = (0, [0] * 60)
    elif (note[1] == 'f'):
        fell_asleep_at_minute = int(datetime.utcfromtimestamp(
            line[0]).strftime('%M'))
    else:
        woke_up_at_minute = int(datetime.utcfromtimestamp(
            line[0]).strftime('%M'))

        worker_matrix_el = worker_matrix[current_guard_id]
        previous_sleeping_time = worker_matrix_el[0]
        arr = worker_matrix_el[1]

        total_sleeping_time = woke_up_at_minute - fell_asleep_at_minute - 1

        # worker_matrix_el[0] = total_sleeping_time
        for i in range(fell_asleep_at_minute, woke_up_at_minute):
            arr[i] = arr[i] + 1
        pass

        worker_matrix[current_guard_id] = (
            previous_sleeping_time + total_sleeping_time, arr)

a = list(worker_matrix.items())
a.sort(key=lambda x: x[1][0])
a.reverse()


minutes = a[0][1][1]
guard_id = a[0][0]
max_minute = minutes.index(max(minutes))
print("Guard ID: %d" % guard_id)
print("Minute: %d" % max_minute)

end = timer()
exec_time = (end - start) * 1000
print("Executon time %f ms" % exec_time)
