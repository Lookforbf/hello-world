public class StringManip {
    final static int CCCODE_STD_LENGTH = 10;//标准长度（去掉分隔符）
    final static int CCCODE_fst_idx=4;
    final static int CCCODE_snd_idx=9;
    final static int CCCODE_trd_idx=11;

    public StringManip(){

    }

    /**
     * 移除码中的分隔符
     * @param rstring
     */
    static public String RemoveSeparator(String rstring){
        rstring=rstring.replaceAll("-","");
        rstring=rstring.replaceAll("/","");
//        rstring=rstring.replaceAll("\\","");
        return rstring;
    }

    static public String AddSeparator(String rstring){
        return rstring.substring(0,CCCODE_fst_idx)+"-"
                +rstring.substring(CCCODE_fst_idx,CCCODE_snd_idx-1)+"-"
                +rstring.substring(CCCODE_snd_idx-1,CCCODE_trd_idx-2)+"-"
                +rstring.substring(CCCODE_trd_idx-2);
    }

    /**
     * 标准格式判断：
     * 1、纯码
     * 2、在规定位置存在分隔符，且分隔符相同
     * 3、符合32进制规范
     * @param rstring
     * @return
     */
    public static boolean isDataLegal(String rstring)throws MyException{
        if(rstring.length()==CCCODE_STD_LENGTH){//长度规范
            if(Base32.Base32Legality(rstring)==0)return true;//32进制规范
        }
        if(rstring.length()==CCCODE_STD_LENGTH+3){//格式规范
            if(Base32.Base32Legality(StringManip.RemoveSeparator(rstring))!=0)return false;
            String fst=rstring.substring(CCCODE_fst_idx,CCCODE_fst_idx+1);
            String snd=rstring.substring(CCCODE_snd_idx,CCCODE_snd_idx+1);
            String trd=rstring.substring(CCCODE_trd_idx,CCCODE_trd_idx+1);
            if(fst.equals(snd) && fst.equals(trd)
                && "-/".contains(fst)
            )return true;
        }
        return false;
    }

}
