/*

    Module : AAP
    Projet : ComputeShaderStudio
    Présenté par : 
        Fatima OULATA 
        Linda Imene BOULMAALI 

    Code inspiré de : https://www.shadertoy.com/view/MdXSzS


*/



void main( )
{
    uint x = gl_GlobalInvocationID.x;
    uint y = gl_GlobalInvocationID.y;
    uint Q = x + y * WSX;

    /*

        vec2 uv = (vec2(x,y) / vec2(WSX,WSY)) - 0.5; 

        Cette opération  normalise les coordonnées x et y par rapport à la taille 
        de la fenêtre  (WSX et WSY). En divisant x et y par la largeur 
        et la hauteur de la fenêtre, respectivement, on obtient des valeurs normalisées 
        comprises entre 0 et 1. 
        En soustrayant 0.5, on centre les coordonnées autour de zéro.

        vec2 : stock deux composantes comme x et y, (position)

    */

    vec2 uv = (vec2(x,y) / vec2(WSX,WSY)) - 0.5; 
    float t;
    float si;
    float co, ab;
    float v1, v2, v3;
    v1 = v2 = v3 = 0.0;
    float len, s = 0.0;
    mat2 ma;

    if(step<200){

        /*
            t = step * 0.09 + ((0.025 + 0.05 * sin(step * 0.1))/(length(uv.xy) + 0.07)) * 2.2; //0.1 pour la rapiditÃ©
            si = sin(t);
            ab = abs(t);
            ma = mat2(co, si, -si, co);

            mat2 est  utilisé pour représenter une matrice 2x2.
            Dans ce contexte, la matrice ma est utilisée pour effectuer une rotation 
            bidimensionnelle. 

        */

        t = step * 0.09 + ((0.025 + 0.05 * sin(step * 0.1))/(length(uv.xy) + 0.07)) * 2.2; //0.1 pour la rapiditÃ©
        si = sin(t);
        ab = abs(t);
        ma = mat2(ab, si, -si, ab);
        for (int i = 0; i < 100; i++){
            vec3 p = s * vec3(uv, 0.0);
            p.xy *= ma;

            // STEP : 0 
            if (step<100){
                p += vec3(0.22, 0.3, s - 1.5 - sin(step * 0.13) * 0.1);
                for (int i = 0; i < 8; i++)    p = sin(p) / dot(p,p) - 0.659;
            }else {
                // STEP: 1
                if  (step<200){
                    p += vec3(0.22, 0.3, s - 1.5 - sin(step * 0.13) * 0.1);
                    for (int i = 0; i <8; i++)    p = cos(p) / dot(p,p) - 0.659;
                    p += vec3(0.22, 0.3, s - 1.5 - sin(step * 0.13) * 0.1);      
                    for (int i = 0; i < 8; i++)    p = abs(p) / dot(p,p) - 0.659;
                }else{
                    // STEP: DEBUT D'EXPLOSION
                    p += vec3(0.22, 0.3, s - 1.5 -log(step * 0.13) * 0.1);
                    for (int i = 0; i < 8; i++)    p = abs(p) / dot(p,p) - 0.9;
                }
            }

            v1 += dot(p,p) * .0015 * (1.8 + sin(length(uv.xy * 13.0) + 0.5  - step * 0.2));
            v2 += dot(p,p) * .0013 * (1.5 + sin(length(uv.xy * 14.5) + 1.2 - step * 0.3));
            v3 += length(p.xy*10.) * 0.0003;
            s  += 0.035;
        }
        /*
            float len = length(uv);
            utilisé pour contrôler des effets en fonction 
            de la distance par rapport à un point central
        */

        len = length(uv);
        v1 *= smoothstep(0.5, 0.0, len);
        v2 *= smoothstep(0.5, 0.0, len);
        v3 *= smoothstep(0., 0.0, len);
    
        vec3 col = vec3( v3 * (1.5 + sin(step * 0.2) * 1),(v1 + v3) * 0.3,v2) 
            + smoothstep(0.2, 0.0, len) * 0.85 + smoothstep(0.0, 0.01, v3) * 0.3;
        
        data_0[Q] = 0xff000000 + (int(col.x))+( int(col.y*66 )<<8) + (int(col.z *90) <<16);

    }else{

        // STEP: EXPLOSION
        if(step<400){
            t = step * 0.02 + (( 0.005 * log(step * 0.1))/(length(uv.xy) + 0.07)) * 2.2; //0.005 c'est ce qui affiche l'absorbation grande 
            si = cos(t);
            ab = abs(t);
            ma = mat2(ab, si, -si, ab);
                
        }else{
            // STEP: GALAXY
            //0.25 et 0.07 et 2.2 ce sont ce qui donne le shape de galaxy 
            t = step * 0.01 + ((0.25 + 0.005 *log(step * 0.09))/(length(uv.xy) + 0.07)) * 2.2; //0.1 pour la rapidité
            si =sin(t);
            co = cos(t);  
            ma = mat2(co, si, -si, co);

        }
        
        for (int i = 0; i < 90; i++){
            vec3 p = s * vec3(uv, 0.0);
            p.xy *= ma;
            p += vec3(0.22, 0.3, s - 1.5 -log(step * 0.13) * 0.1);
            for (int i = 0; i < 8; i++)    p = abs(p) / dot(p,p) - 0.9;
            v1 += dot(p,p) * .0015 * (1.8 +sin(length(uv.xy * 13.0) + 0.5  - step * 0.2));
            v2 += dot(p,p) * .0013 * (1.5 +sin(length(uv.xy * 14.5) + 1.2 - step * 0.3));
            v3 += length(p.xy*10.) * 0.0003;
            s  += 0.035;
        }
        
        len = length(uv);
        v1 *= smoothstep(0.5, 0.0, len);
        v2 *= smoothstep(0.5, 0.0, len);
        v3 *= smoothstep(0.9, 0.0, len);

        /*
            La fonction ceil est utilisée pour arrondir un nombre à l'entier supérieur le plus proche. 
        */

        vec3 col = vec3( v3 * (1.5 + ceil(step * 0.2) * 1),(v1 + v3) * 0.3,v2) 
            + smoothstep(0.2, 0.0, len) * 0.85 + smoothstep(0.0, 0.6, v3) * 0.3;
        data_0[Q] = 0xff000000 + (int(col.x))+( int(col.y*60)<<8) + (int(col.z *90) <<16);
    } 
}
