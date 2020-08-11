package com.example.calculatorstry2;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;

import com.google.android.material.textfield.TextInputLayout;

public class RomeNumbersFragment extends Fragment {
    private AutoCompleteTextView chooserUpper, chooserDowner;
    private TextInputLayout editUpper, editDowner;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_rome_numbers, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        final String[] items = {getResources().getString(R.string.rome_numbers), getResources().getString(R.string.arab_numbers)};
        chooserUpper = view.findViewById(R.id.rome_num_textView_upper);
        chooserUpper.setAdapter(new ArrayAdapter<>(requireContext(), R.layout.support_simple_spinner_dropdown_item, items));
        chooserDowner = view.findViewById(R.id.rome_number_textView_downer);
        chooserDowner.setAdapter(new ArrayAdapter<>(requireContext(), R.layout.support_simple_spinner_dropdown_item, items));
        editUpper = view.findViewById(R.id.textInputLayout2);
        editDowner = view.findViewById(R.id.textInputLayout4);

        view.findViewById(R.id.shapeableImageView2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String tmp = chooserUpper.getText().toString();
                chooserUpper.setText(chooserDowner.getText().toString());
                chooserUpper.setAdapter(new ArrayAdapter<>(requireContext(), R.layout.support_simple_spinner_dropdown_item, items));
                chooserDowner.setText(tmp);
                chooserDowner.setAdapter(new ArrayAdapter<>(requireContext(), R.layout.support_simple_spinner_dropdown_item, items));
            }
        });

        editUpper.getEditText().addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                editDowner.getEditText().setText(String.valueOf(MainActivity.romeToArab(s.toString())));
            }

            @Override
            public void afterTextChanged(Editable s) {

            }
        });
    }
}