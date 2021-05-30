fn bubble_sort(list: &mut [i32]) {
    let mut flag = true;

    while flag {
        flag = false;
        for i in 1..list.len() {
            if list[i - 1] > list[i] {
                let temp = list[i - 1];
                list[i - 1] = list[i];
                list[i] = temp;

                flag = true;
            } 
        }
    }
}

fn insert_sort(list: &mut [i32]) {
    for i in 0..list.len() {
        let mut temp = list[i];

        for j in 0..i {
            if temp < list[j] {
                let temp2 = list[j];
                list[j] = temp;
                temp = temp2;
            }
        }

        list[i] = temp;
    }
}

fn merge(first_half: &[i32], second_half: &[i32], result: &mut [i32]) {
    let mut result_index = 0;

    let mut i = 0;
    let mut j = 0;
    while (i < first_half.len()) && (j < second_half.len()) {
        if first_half[i] <= second_half[j] {
            result[result_index] = first_half[i];
            i += 1;
        } else {
            result[result_index] = second_half[j];
            j += 1;
        }
        result_index += 1;
    }

    if i != first_half.len() {
        &mut result[result_index..].copy_from_slice(&first_half[i..first_half.len()]);
    }

    if j != second_half.len() {
        &mut result[result_index..].copy_from_slice(&second_half[j..second_half.len()]);
    }
}

fn merge_sort(list: &mut [i32]) {
    let length = list.len();

    if (length == 0) || (length == 1) {
        return
    }

    let (first_half, second_half) = list.split_at_mut(length / 2);

    merge_sort(first_half);
    merge_sort(second_half);

    let mut result = vec!(0; length);
    merge(first_half, second_half, result.as_mut_slice());
    list.copy_from_slice(result.as_slice());
}

fn print_slice(list: &[i32]) {
    for number in list.iter() {
        print!("{} ", number);
    }
    println!();
}

fn main() {
    let mut list_of_numbers = [7, 6, 1, 2, 5];

    print_slice(&list_of_numbers);

    merge_sort(&mut list_of_numbers);

    print_slice(&list_of_numbers);
}
