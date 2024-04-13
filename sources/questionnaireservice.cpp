#include "questionnaireservice.h"

QuestionnaireService::QuestionnaireService()
{

}

QString whatDoesCharSay (char oui) {
    if (oui == 'o') {
        return "oui";
    } else if (oui == 'n') {
        return "non";
    }
    return "";
}

bool yesChar (char c) {
    return c == 'o';
}

QString structures (prise_en_charge pec) {
    QStringList retour;
    if (yesChar(pec.ime)) {
        retour.push_back("IME");
    }
    if (yesChar(pec.cams)) {
        retour.push_back("CAMS");
    }
    if (yesChar(pec.hopital_de_jour)) {
        retour.push_back("Hôpital de jour");
    }
    if (yesChar(pec.uema)) {
        retour.push_back("UEMA");
    }
    if (yesChar(pec.sessad)) {
        retour.push_back("SESSAD");
    }
    if (yesChar(pec.rased)) {
        retour.push_back("RASED");
    }
    if (yesChar(pec.segpa)) {
        retour.push_back("SEGPA");
    }
    if (yesChar(pec.ulis)) {
        retour.push_back("ULIS");
    }
    if (yesChar(pec.liberal)) {
        retour.push_back("Liberal");
    }
    if (!pec.autre_structure.isEmpty())
        retour.push_back(pec.autre_structure);
    return retour.join(',');
}

QString careType(prise_en_charge pec) {
    QStringList retour;
    if (pec.orthophonie == 'o') {
        retour.push_back("orthophonie");
    }
    if (pec.psychomotricite == 'o') {
        retour.push_back("psychomotricité");
    }
    if (pec.ergotherapie == 'o') {
        retour.push_back("ergothérapie");
    }
    if (pec.educatrice == 'o') {
        retour.push_back("éducatrice");
    }
    if (pec.psychologie == 'o') {
        retour.push_back("psychologie");
    }
    if (pec.neuropsychologie == 'o') {
        retour.push_back("neuropsychologie");
    }
    if(!pec.autre_type.isEmpty())
        retour.push_back(pec.autre_type);
    return retour.join(',');
}

QString choixAliment(alimentation_enfant ae) {
    QStringList retour;
    if (ae.selon_structure == 'o') {
        retour.push_back("structure");
    }
    if (ae.selon_couleur == 'o') {
        retour.push_back("couleur");
    }
    if (ae.selon_temperature == 'o') {
        retour.push_back("température");
    }
    if (ae.selon_odeur == 'o') {
        retour.push_back("odeur");
    }
    if (ae.selon_gout == 'o') {
        retour.push_back("goût");
    }
    if (retour.isEmpty()) {
        return "";
    }
    return "selon " + retour.join(',');
}

QString difficulteAlimentaire(alimentation_enfant ae) {
    QStringList retour;
    if (ae.pb_mastication == 'o') {
        retour.push_back("mastication");
    }
    if (ae.pb_deglutir == 'o') {
        retour.push_back("deglutir");
    }
    if (ae.pb_digestion == 'o') {
        retour.push_back("digestion");
    }
    return retour.join(',');
}

QString difficulteSommeilType (sommeil_enfant se) {
    QStringList retour;
    if(se.endormissement == 'o') {
        retour.push_back("endormissement");
    }
    if(se.reveil_nocturne == 'o') {
        retour.push_back("réveil nocturne");
    }
    if(se.reveil_precoce == 'o') {
        retour.push_back("réveil précoce");
    }
    return retour.join(',');
}

QString QuestionnaireService::toString()
{
    QString retour = prenom + " " + nom + ";";
    retour += num_inclusion + ";";
    retour += ";";
    retour += date_naissance + ";";
    retour += sexe == 'H' ? "masculin" : sexe == 'F' ? "féminin" : ""; retour += ";";
    retour += date_inclusion + ";";
    retour += date_test + ";";
    retour += nom_codateur + ";";
    retour += centre + ";";

    // trouble spectre autisme
    trouble_spectre_autisme tsa = troubleSpectreAutisme;
    retour += whatDoesCharSay(tsa.diagnostic_de_trouble) + ";";
    retour += tsa.a_quel_age + ";";
    retour += tsa.pose_par + ";";
    retour += tsa.score_adi + ";";
    retour += tsa.score_ados + ";";
    retour += tsa.score_qi + ";";
    retour += tsa.score_autre_test + ";";

    // autre diagnostic
    autre_diagnostic ad = autreDiagnostic;
    retour += whatDoesCharSay(ad.trouble_attention_avec_hyperactivite) + ";";
    retour += whatDoesCharSay(ad.trouble_attention_sans_hyperactivite) + ";";
    retour += whatDoesCharSay(ad.trouble_communication_sociale) + ";";
    retour += whatDoesCharSay(ad.trouble_communication_non_specifie) + ";";
    retour += whatDoesCharSay(ad.trouble_moteurs) + ";";
    retour += whatDoesCharSay(ad.trouble_apprentissages) + ";";
    retour += whatDoesCharSay(ad.trouble_phonation) + ";";
    retour += ad.autre + ";";

    // diagnostic psychiatrique
    diagnostic_psychiatrique dp = diagnosticPsychiatrique;
    retour += whatDoesCharSay(dp.trouble_anxieux) + ";";
    retour += dp.type + ";";
    retour += whatDoesCharSay(dp.trouble_obsessionnel) + ";";
    retour += whatDoesCharSay(dp.trouble_stress) + ";";

    // structure
    prise_en_charge pec = priseEnCharge;
    retour += structures(pec) + ";";
    retour += careType(pec) + ";";

    // traitement medicamentaux
    traitement_medicamentaux tm = traitementMedicamentaux;
    retour += whatDoesCharSay(tm.prend_il_un_traitement) + ";";
    retour += tm.traitement + ";";

    // sommeil
    sommeil_enfant se = sommeilEnfant;
    retour += whatDoesCharSay(se.difficulte_de_sommeil) + ";";
    retour += difficulteSommeilType(se) + ";";
    retour += whatDoesCharSay(se.apnee_du_sommeil) + ";";
    retour += whatDoesCharSay(se.terreur_nocturne) + ";";
        // si oui
    retour += whatDoesCharSay(se.frequent_terreur_nocturne) + ";";

    retour += whatDoesCharSay(se.diagnostic_trouble_de_sommeil) + ";";

    // aliment
    alimentation_enfant ae = alimentationEnfant;
    retour += whatDoesCharSay(ae.presente_selectivite_alimentaire) + ";";
        // si oui
    retour += ae.intensite_selectivite + ";";
    retour += choixAliment(ae) + ";";
    retour += difficulteAlimentaire(ae) + ";";


    // Langage
    langage_enfant le = langageEnfant;
    retour += le.niveau_langage + ";";
    retour += le.age_premiers_mots + ";";


    // Moteur
    moteur_enfant me = moteurEnfant;
    retour += whatDoesCharSay(me.retard_moteur) + ";";
    retour += me.age_premiere_marche + ";";
    retour += whatDoesCharSay(me.diagnostice_de_dyspraxie) + ";";
    retour += whatDoesCharSay(me.probleme_de_coordination) + ";";
    retour += whatDoesCharSay(me.difficulte_de_lateralisation) + ";";
    retour += whatDoesCharSay(me.difficulte_de_reperer_dans_lespace) + ";";
    retour += whatDoesCharSay(me.difficulte_de_motricite_fine) + ";";

    // Apprentissage
    apprentissages_enfant ape = apprentissageEnfant;
    retour += whatDoesCharSay(ape.presente_dyslexie) + ";";
    retour += whatDoesCharSay(ape.difficulte_lecture) + ";";
    retour += whatDoesCharSay(ape.difficulte_ecriture) + ";";
    retour += whatDoesCharSay(ape.difficulte_calcul) + ";";
    retour += ape.autre;

    return retour;
}
