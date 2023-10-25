std::vector<int> CSRtoCOO_converter(){
        std::vector<int> rows_coordinates;

        rows_coordinates.resize(values.size());
        unsigned int count=0, index=0, diff;

        for(unsigned int i=0; i<rows_idx.size(); i++){
            if(rows_idx[i]!=0 && rows_idx[i]>rows_idx[i-1]){
                diff=rows_idx[i]-rows_idx[i-1];
                for(unsigned int j=0; j<diff; j++){
                    rows_coordinates[index]=i-1;
                    index++;
                }
            }
        }

        for(int i=0; i<rows_coordinates.size(); i++){
            std::cout<<rows_coordinates[i]<<"\t";
        }

        return rows_coordinates;
    }


std::vector<int> COOtoCSR_converter(){
        std::vector<int> row_idx;
        //I need the number of the rows and the size of number of non-zero element inside the sparse amtrix
        const int numRows=this->n_row();

        row_idx.resize(numRows+1);
        
        row_idx[0]=0;
        unsigned int count=0;

        for(unsigned int i=0; i<size; i++){
            for(unsigned int j=0; j<size; j++){
                if(rows[j]==i){
                    count++;
                    row_idx[i+1]=count;
                }
                //case in which the row has all zero elements
                else if(rows[j]!=i){
                    row_idx[i+1]=count;
                }
            }
        }

        for(int i=0; i<numRows+1; i++){
            std::cout<<row_idx[i]<<"\t";
        }
        std::cout<<std::endl;
        return row_idx;
    }
