import os

dirname = os.path.dirname(__file__)

with open(os.path.join(dirname, "data/output.csv"), 'a') as output_file:
    for index, filename in enumerate(os.listdir(os.path.join(dirname, "data"))):
        with open(os.path.join(dirname, "data", filename), 'r') as input_file:
            #for first csv file we copy the header, for the rest only data
            lines = input_file.readlines()

            if index == 0:
                output_file.writelines(lines)
            else:
                output_file.writelines(lines[1:])