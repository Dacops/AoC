def bingo(file):
    with open(file,'r') as f:
        lst = f.readlines()
        sequence = lst[0].split(',')
        boards = []
        for i in range(int(len(lst)/6)):
            boards.append(lst[1:][6*i+1:6*(i+1)])
        
    def calculator(board_number, number, rows_and_columns):
        board, total = rows_and_columns[10*int(board_number):10*(int(board_number)+1)-5], 0
        for row in board:
            for num in row:
                total+=int(num)
        return total*int(number)
    
    rows_and_columns = []
    for board in boards:
        rows=[]
        for row in board:
            row=row.split()
            rows_and_columns.append(row)
            rows.append(row)
        for i in range(len(rows)):
            column=[]
            for row in rows:
                column.append(row[i])
            rows_and_columns.append(column)

    for number in sequence:
        for row_or_column in rows_and_columns:
            if number in row_or_column:
                row_or_column.remove(number)
            if row_or_column==[]:
                return calculator(int((rows_and_columns.index([]))/10), number, rows_and_columns)