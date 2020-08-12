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
import com.google.android.material.textview.MaterialTextView;

import java.util.Objects;

public class RomeNumbersFragment extends Fragment {
    private AutoCompleteTextView chooserUpper;
    private MaterialTextView chooserDowner;
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
        editUpper = view.findViewById(R.id.textInputLayout2);
        editDowner = view.findViewById(R.id.textInputLayout4);
        editDowner.setEnabled(false);

        view.findViewById(R.id.shapeableImageView2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String tmp = chooserUpper.getText().toString();
                chooserUpper.setText(chooserDowner.getText().toString());
                chooserUpper.setAdapter(new ArrayAdapter<>(requireContext(), R.layout.support_simple_spinner_dropdown_item, items));
                chooserDowner.setText(tmp);
                tmp = editUpper.getEditText().getText().toString();
                editUpper.getEditText().setText(editDowner.getEditText().getText().toString());
                editDowner.getEditText().setText(tmp);
            }
        });

        editUpper.getEditText().addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                if (chooserUpper.getText().toString().equals(getResources().getString(R.string.rome_numbers))) {
                    editDowner.getEditText().setText(String.valueOf(MainActivity.romeToArab(s.toString())));
                }
                if (chooserUpper.getText().toString().equals(getResources().getString(R.string.arab_numbers))) {
                    editDowner.getEditText().setText(String.valueOf(MainActivity.arabToRome(s.toString())));
                }
            }

            @Override
            public void afterTextChanged(Editable s) {

            }
        });

        chooserUpper.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
            }

            @Override
            public void afterTextChanged(Editable s) {
                if (chooserUpper.getText().toString().equals(getResources().getString(R.string.rome_numbers))) {
                    chooserDowner.setText(getResources().getString(R.string.arab_numbers));
                }
                if (chooserUpper.getText().toString().equals(getResources().getString(R.string.arab_numbers))) {
                    chooserDowner.setText(getResources().getString(R.string.rome_numbers));
                }
            }
        });
    }
}