import requests
import sys
import os
from datetime import datetime, timedelta
"""
        В 2-х ниже приведённых траях отлавливаются ошибки связанные с соединением 
    с апишками и со стабильностью их работы 
"""
try:
    response_user = requests.get('https://json.medrating.org/users')
    response_user.raise_for_status()
except requests.exceptions.ConnectionError:
    print('(user)Connection error')
    sys.exit()
except requests.exceptions.HTTPError as err:
    print(f'(user)HTTP Error:{err}')
    sys.exit()

try:
    response_tasks = requests.get('https://json.medrating.org/todos')
    response_tasks.raise_for_status()
except requests.exceptions.ConnectionError:
    print('(user)Connection error')
    sys.exit()
except requests.exceptions.HTTPError as err:
    print(f'(user)HTTP Error:{err}')
    sys.exit()

"""Список основных констант скрипта"""
USERS = response_user.json()
TASKS = response_tasks.json()
PATH = os.path.join(os.getcwd(), 'tasks')


def record_time_format():
    """
            Функция предназначина для приведения время компьютера
        к формату, приведённому в файле с заданием, при чем
        к формату записи который используется для записи времени
        в файл.
    """
    formatted_time = datetime.today().strftime('%d.%m.%Y %H:%M')
    return formatted_time


def filename_time_format(file_name):
    """
            Функция суть которой аналогична предыдущей, только
        для записи времени в имя файла.
    """
    with open(file_name, 'r') as f:
        line = f.readline()
        data_string = line[len(line) - 17:len(line) - 1]
        datetime_cast = datetime.strptime(data_string, '%d.%m.%Y %H:%M')
        formatted_time = datetime_cast.strftime('%Y-%m-%dT%H-%M')
    return formatted_time


def str_control(string):
    """Функция осуществляющая контроль длины строки"""
    if len(string) > 50:
        if string[50] == ' ':
            return string[0:49]+'...'
        else:
            return string[0:50]+'...'
    else:
        return string


def get_user_report(user):
    """
            Функция записывающая в строку, которая в последствии
        будет выводится в файл, всю необходимую по заданию информацию.
        Решение записи всей инфы в один файл,было принято для удобного,
        на мой взгляд, осуществления контроля записи данных на диск.
    """
    completed_tasks = ''
    unfinished_tasks = ''
    for task in TASKS:
        if user['id'] == task['userId']:
            if task['completed']:
                completed_tasks += str_control(task['title'])+'\n'
            else:
                unfinished_tasks += str_control(task['title'])+'\n'
    user_report = '{} <{}> {}\n'.format(user['name'], user['email'], record_time_format())
    user_report += user['company']['name']+'\n\n'
    user_report += 'Завершенные задачи:\n'
    if completed_tasks == '':
        user_report += 'У пользователя нет завершенных задач\n\n'
    else:
        user_report += completed_tasks+'\n'

    user_report += 'Незавершенные задачи:\n'
    if unfinished_tasks == '':
        user_report += 'У пользователя нет задач\n\n'
    else:
        user_report += unfinished_tasks+'\n'
    return user_report


def check_time_creation(file_name):
    """
            Функция для проверки равенства времени в уже записанном файле
        пользователя, с текущим временем(с точнойтью до минуты).
        Без этой проверки в результате выполнения скрипта может возбникнуть
        ситуация, когда создастся файл с таким же именем, как у уже существующего
        файла.
    """
    now = datetime.now()
    file_date = datetime.strptime(filename_time_format(file_name), '%Y-%m-%dT%H-%M')
    if now - file_date < timedelta(minutes=1):
        print('You cannot create a new report more than once minute.')
        sys.exit()


"""Проверка на существование деректории /tasks"""
if not(os.path.exists(PATH)):
    os.mkdir(PATH)

"""
        Основной алгоритм скрипта.
"""
for user in USERS:
    filename = os.path.join(PATH, user['username']+'.txt')
    new_filename = ''
    user_rep = get_user_report(user)
    if os.path.exists(filename):
        check_time_creation(filename)
        new_filename = '{}_{}.txt'.format(filename[0:len(filename) - 4], filename_time_format(filename))
        os.renames(filename, new_filename)
    try:
        with open(filename, 'w') as f:
            f.write(user_rep)
    except IOError:
        print('Error writing to disk for user: {}'.format(user['username']))
        if os.path.exists(filename):
            os.remove(filename)
        if os.path.exists(new_filename):
            os.rename(new_filename, filename)


